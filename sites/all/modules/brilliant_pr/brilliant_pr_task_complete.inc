<?php

/**
 * Callback function. here we prepare complete table for task
 * @return array
 */

function brilliant_pr_task_list_complete() {
  global $user;
  //Create a list of headers for Html table
  if (in_array('administrator', $user->roles) || in_array('curator', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'tid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Project ref')),
      array('data' => t('Total time spent')),
      array('data' => t('Implementor'), 'field' => 'time_spent'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Author')),
      array('data' => t('Author\'s email')),
      array('data' => t('Delete task')),
    );
  }
  elseif (in_array('implementor', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'tid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Project ref')),
      array('data' => t('Total time spent')),
      array('data' => t('Curator'), 'field' => 'time_spent'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Author')),
      array('data' => t('Author\'s email')),
    );
  }
  else {
    $header = array(
      array('data' => t('ID'), 'field' => 'tid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Project ref')),
      array('data' => t('Total time spent')),
      array('data' => t('Curator')),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
    );
  }
//Create the Sql query.
  $query = db_select('brilliant_pr_task', 't')
    ->condition('status', '1', '=') //wait projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(5) //5 results per page
    ->extend('TableSort') //Sorting Extender
    ->orderByHeader($header)//Field to sort on is picked from $header
    ->fields('t', array(
      'tid',
      'title',
      'ref',
      'created',
      'dead_time',
      'uid',
      'implementor',
      'curator',
    ));
  $results = $query
    ->execute();
  $rows = array();
  foreach ($results as $entity) {
    $project_entity = brilliant_pr_project_load($pid = $entity->ref);
    if ($user->uid && $account = user_load($entity->uid)) {
      if ($user->name == $entity->curator || in_array('administrator', $user->roles) || $user->name == $entity->implementor || $user->name == $project_entity->customer_name) {
        $user_name = $account->uid;
        $user_mail = $account->mail;
        $implementor = user_load_by_name($entity->implementor);
        $curator = user_load_by_name($entity->curator);
        if (in_array('administrator', $user->roles) || in_array('curator', $user->roles)) {
          $rows[] = array(
            'data' => array(
              $entity->tid,
              l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
              isset($project_entity->pid) ? l($project_entity->title, 'entity/brilliant_pr_project/basic/' . $project_entity->pid) : '-',
              '-',
              get_name($implementor->uid),
              format_date($entity->created),
              date('Y-m-d H:i:s', $entity->dead_time),
              l(get_name($user_name), 'user/' . $entity->uid),
              l($user_mail, 'mailto:' . $user_mail),
              l(t('delete'), 'entity/brilliant_pr_task/basic/' . $entity->tid . '/remove'),
            )
          );
          #end row[]
        }
        elseif ($user->name == $entity->implementor) {
          $rows[] = array(
            'data' => array(
              $entity->tid,
              l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
              isset($project_entity->pid) ? l($project_entity->title, 'entity/brilliant_pr_project/basic/' . $project_entity->pid) : '-',
              '-',
              get_name($curator->uid),
              format_date($entity->created),
              date('Y-m-d H:i:s', $entity->dead_time),
              l(get_name($user_name), 'user/' . $entity->uid),
              l($user_mail, 'mailto:' . $user_mail),
            )
          );
          #end row[]
        }
        else {
          $rows[] = array(
            'data' => array(
              $entity->tid,
              l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
              isset($project_entity->pid) ? l($project_entity->title, 'entity/brilliant_pr_project/basic/' . $project_entity->pid) : '-',
              '-',
              get_name($implementor->uid),
              format_date($entity->created),
              date('Y-m-d H:i:s', $entity->dead_time),
            )
          );
          #end row[]
        }
      }
    }
  } #end foreach
  if (!empty($entity) && $user->name == $entity->curator || !empty($entity) && $user->name == $entity->implementor
    || !empty($entity) && in_array('administrator', $user->roles) || !empty($entity) && in_array('customer', $user->roles)
  ) {
    $content = t('Hello') . ', ' . get_name($user->uid) . '<br>';
    if (in_array('administrator', $user->roles)) {
      $content .= l(t('Delete all tasks'), 'entity/brilliant_pr_task/basic/remove_all');
    }
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Completed tasks') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => t('Not found any completed task.'),
          //Optional empty text for the table if result test is empty
        )
      );
    $html .= theme('pager',
      array(
        'tags' => array(),
      )
    );
  }
  else {
    $content = '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any completed tasks.') .'</div>';
    $html = $content;
  }
  return ($html);
}