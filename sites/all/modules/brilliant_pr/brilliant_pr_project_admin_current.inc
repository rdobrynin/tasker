<?php

/**
 * Provide a list of project existing entities and the ability to add more.
 * Tabs provide field and display admin management.
 */

function brilliant_pr_project_admin_page() {
  global $user;
  //Create a list of headers for Html table
  if (in_array('administrator', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Total tasks')),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Status'), 'field' => 'status'),
      array('data' => t('CTS')),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('Changed'), 'field' => 'changed'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer')),
      array('data' => t('Author')),
      array('data' => t('Author\'s email')),
      array('data' => t('Edit project')),
    );
  }
  else {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Total tasks')),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Status'), 'field' => 'status'),
      array('data' => t('CTS')),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('Changed'), 'field' => 'changed'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer')),
      array('data' => 'Edit project'),
    );
  }
//Create the Sql query.
  $query = db_select('brilliant_pr_project', 'p')
    ->condition('status', '5', '!=') //wait projects
    ->condition('status', '3', '!=') //complete projects
    ->condition('status', '1', '!=') //approve projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(10) //10 results per page
    ->extend('TableSort') //Sorting Extender
    ->orderByHeader($header)//Field to sort on is picked from $header
    ->fields('p', array(
      'pid',
      'title',
      'status',
      'created',
      'changed',
      'opt_time',
      'dead_time',
      'uid',
      'customer_name',
      'curator',
    ));

  $results = $query
    ->execute();
  $rows = array();
  foreach ($results as $entity) {
    if ($user->uid && $account = user_load($entity->uid)) {
      $user_name = $account->uid;
      $user_mail = $account->mail;
      $counter = 0; // make counter in cycle (to know how many tasks per project)
      $tasks = brilliant_pr_task_load_multiple();
      foreach ($tasks as $task) {
        if ($entity->pid == $task->ref && $task->status !=5) {
          $counter++;
        }
      }
      $customer_name = user_load_by_name($entity->customer_name);
      if (in_array('administrator', $user->roles)) {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            $counter == 0 ? '-' : l(t($counter), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/tasks'),
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            brilliant_pr_project_status_position_title($entity->status),
            '--',
            format_date($entity->created),
            format_date($entity->changed),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            l(get_name($user_name), 'user/' . $entity->uid),
            l($user_mail, 'mailto:' . $user_mail),
            ($entity->status == 3) ? l(t('completed'), 'admin/structure/brilliant_pr_project/manage/complete') :
              l(t('edit'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/edit'),
          )
        );
        #end row[]
      }
      elseif ($user->name == $entity->curator) {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            $counter == 0 ? '-' : l(t($counter), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/tasks'),
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            brilliant_pr_project_status_position_title($entity->status),
            '--',
            format_date($entity->created),
            format_date($entity->changed),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            ($entity->status == 3) ? l(t('completed'), 'admin/structure/brilliant_pr_project/manage/complete') :
              l(t('edit'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/edit'),
          )
        );
        #end row[]
      }
    }
  } #end foreach
  if (!empty($entity)) {
    $content = '';
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Current projects') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any current projects.') .'</div>',
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
    $content = '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any current projects.') .'</div>';
    $html = $content;

  }
  return ($html);
}
