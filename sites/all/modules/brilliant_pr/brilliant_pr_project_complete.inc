<?php

/**
 * Provide a list of project existing entities and the ability to add more.
 * Tabs provide field and display admin management.
 */

function brilliant_pr_project_list_complete() {
  global $user;

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
      array('data' => t('Delete project')),
    );
  }
  elseif (in_array('customer', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Total tasks')),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Status'), 'field' => 'status'),
      array('data' => t('CTS')),
      array('data' => t('Curator'), 'field' => 'customer_name'),
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
      array('data' => t('Delete project')),
    );
  }
//Create the Sql query.
  $query = db_select('brilliant_pr_project', 'p')
    ->condition('status', '3', '=') //remove projects
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
  $results = $query
    ->execute();
  $rows = array();
  foreach ($results as $entity) {
    if ($user->uid && $account = user_load($entity->uid)) {
      if ($user->name == $entity->curator) {
        $counter = 0; // make counter in cycle (to know how many tasks per project)
        $tasks = brilliant_pr_task_load_multiple();
        foreach ($tasks as $task) {
          if ($entity->pid == $task->ref) {
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
            l(t('delete'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/remove'),
          )
        );
        #end row[]
      }
      elseif (in_array('administrator', $user->roles)) {
        $counter = 0; // make counter in cycle (to know how many tasks per project)
        $tasks = brilliant_pr_task_load_multiple();
        foreach ($tasks as $task) {
          if ($entity->pid == $task->ref) {
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
            l(get_name($curator->uid), 'user/' . $curator->uid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
            l(t('delete'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/remove'),
          )
        );
        #end row[]
      }
      elseif ($user->name == $entity->customer_name) {
        $counter = 0; // make counter in cycle (to know how many tasks per project)
        $tasks = brilliant_pr_task_load_multiple();
        foreach ($tasks as $task) {
          if ($entity->pid == $task->ref) {
            $counter++;
          }
        }
        $curator = user_load_by_name($entity->curator);
        $rows[] = array(
          'data' => array(
            $entity->pid,
            $counter == 0 ? '-' : l(t($counter), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/tasks'),
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            brilliant_pr_project_status_position_title($entity->status),
            '-',
            l(get_name($curator->uid), 'user/' . $curator->uid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
          )
        );
        #end row[]
      }
    }
  } #end foreach
  if (!empty($entity) && $user->uid && $account = user_load($entity->uid)) {
    $content = '';
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Complete projects') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any completed projects.') .'</div>',
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
    $content = '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any completed projects.') .'</div>';
    $html = $content;

  }
  return ($html);
}