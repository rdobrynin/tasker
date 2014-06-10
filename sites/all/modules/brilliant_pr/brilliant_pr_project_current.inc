<?php

/**
 * Provide a list of project existing entities and the ability to add more.
 * Tabs provide field and display admin management.
 */

function brilliant_pr_project_info_page() {
  global $user;
  if ($user->uid == in_array('implementor', $user->roles)) {
    drupal_goto($path = 'entity/brilliant_pr_task');
  }
  //Create a list of headers for Html table
  if (in_array('administrator', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Total tasks')),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Status'), 'field' => 'status'),
      array('data' => t('CTS')),
      array('data' => t('Customer'), 'field' => 'customer_name'),
      array('data' => t('Curator'), 'field' => 'curator'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
    );
  }
  else {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Total tasks')),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Status'), 'field' => 'status'),
      array('data' => t('CTS')),
      array('data' => t('Customer'), 'field' => 'customer_name'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
    );
  }
//Create the Sql query.
  if (in_array('customer', $user->roles)) {
    $query = db_select('brilliant_pr_project', 'p')
      ->condition('status', '5', '!=') //remove projects
      ->extend('PagerDefault') //Pager Extender
      ->limit(10) //10 results per page
      ->extend('TableSort') //Sorting Extender
      ->orderByHeader($header)//Field to sort on is picked from $header
      ->fields('p', array(
        'pid',
        'title',
        'status',
        'created',
        'opt_time',
        'dead_time',
        'uid',
        'customer_name',
        'curator',
      ));
  }
  else {
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
        'opt_time',
        'dead_time',
        'uid',
        'customer_name',
        'curator',
      ));
  }
  $results = $query
    ->execute();
  $rows = array();
  foreach ($results as $entity) {
    if ($user->uid && $account = user_load($entity->uid)) {
      if ($user->name == $entity->curator || $user->name == $entity->customer_name) {
        $counter = 0; // make counter in cycle (to know how many tasks per project)
        $tasks = brilliant_pr_task_load_multiple();
        foreach ($tasks as $task) {
          if ($entity->pid == $task->ref && $task->status !=5) {
            $counter++;
          }
        }
        $customer_name = user_load_by_name($entity->customer_name);
        $rows[] = array(
          'data' => array(
            $entity->pid,
            $counter == 0 ? '-' : l(t($counter), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/tasks'),
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            brilliant_pr_project_status_position_title($entity->status),
            '-',
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
          )
        );
        #end row[]
      }
      elseif (in_array('administrator', $user->roles)) {
        $counter = 0; // make counter in cycle (to know how many tasks per project)
        $tasks = brilliant_pr_task_load_multiple();
        foreach ($tasks as $task) {
          if ($entity->pid == $task->ref && $task->status !=5) {
            $counter++;
          }
        }
        $customer_name = user_load_by_name($entity->customer_name);
        $curator = user_load_by_name($entity->curator);
        $rows[] = array(
          'data' => array(
            $entity->pid,
            $counter == 0 ? '-' : l(t($counter), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/tasks'),
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            brilliant_pr_project_status_position_title($entity->status),
            '-',
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            l($entity->curator, 'user/' . $curator->uid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
          )
        );
        #end row[]
      }
    }
  } #end foreach
  if (!empty($entity) && $user->name == $entity->curator || !empty($entity) && $user->name == $entity->customer_name || in_array('administrator', $user->roles)) {
    $content = '';
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Current projects') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' =>'<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any current projects.') .'</div>',
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
