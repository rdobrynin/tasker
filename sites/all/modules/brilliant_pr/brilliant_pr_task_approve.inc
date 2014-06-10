<?php

/**
 * Callback function. here we prepare approve table for projects
 * @return array
 */

function brilliant_pr_task_approve_page() {
  global $user;
  //Create a list of headers for Html table
  $header = array(
    array('data' => t('ID'), 'field' => 'tid', 'sort' => 'asc'),
    array('data' => t('Title'), 'field' => 'title'),
    array('data' => t('Project ref')),
    array('data' => t('Created'), 'field' => 'created'),
    array('data' => t('OPT'), 'field' => 'opt_time'),
    array('data' => t('DDT'), 'field' => 'dead_time'),
  );
//Create the Sql query.
  $query = db_select('brilliant_pr_task', 't')
    ->condition('status', '0', '=') //wait projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(5) //5 results per page
    ->extend('TableSort') //Sorting Extender
    ->orderByHeader($header)//Field to sort on is picked from $header
    ->fields('t', array(
      'tid',
      'title',
      'ref',
      'created',
      'opt_time',
      'dead_time',
      'uid',
    ));
  $results = $query
    ->execute();
  $rows = array();
  foreach ($results as $entity) {
    $project_entity = brilliant_pr_project_load($pid = $entity->ref);
    if ($user->uid && $account = user_load($entity->uid) && $user->name == $project_entity->curator) {
      $rows[] = array(
        'data' => array(
          $entity->tid,
          l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
          l($project_entity->title, 'entity/brilliant_pr_project/basic/' . $project_entity->pid),
          format_date($entity->created),
          date('Y-m-d H:i:s', $entity->opt_time),
          date('Y-m-d H:i:s', $entity->dead_time),
        )
      );
      #end row[]
    }
  } #end foreach
  if (!empty($entity)) {
    $content = t('Hello') . ', ' . get_name($user->uid) . '<br>';
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Tasks for approve') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => t('No one task for approve found.'),
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
    $content = '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any tasks for approve.') .'</div>';
    $html = $content;
  }
  return ($html);
}