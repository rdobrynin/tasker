<?php

/**
 * Callback function. here we prepare remove table for projects
 */

function brilliant_pr_project_remove_page() {
  global $user;
  //Create a list of headers for Html table
  if (in_array('administrator', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('Changed'), 'field' => 'changed'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer'), 'field' => 'customer_name'),
      array('data' => t('Curator'), 'field' => 'curator'),
      array('data' => t('Restore')),
      array('data' => t('Purge')),
    );
  }
  else {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('Changed'), 'field' => 'changed'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer'), 'field' => 'customer_name'),
      array('data' => t('Restore')),
      array('data' => t('Purge')),
    );
  }
//Create the Sql query.
  $query = db_select('brilliant_pr_project', 'p')
    ->condition('status', '5', '=') //wait projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(5) //5 results per page
    ->extend('TableSort') //Sorting Extender
    ->orderByHeader($header)//Field to sort on is picked from $header
    ->fields('p', array(
      'pid',
      'title',
      'created',
      'changed',
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
      $customer_name = user_load_by_name($entity->customer_name);
      $curator = user_load_by_name($entity->curator);
      if (in_array('administrator', $user->roles)) {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            format_date($entity->created),
            format_date($entity->changed),
            date('Y-m-d', $entity->dead_time),
            l($entity->customer_name, 'user/' . $customer_name->uid),
            l($entity->curator, 'user/' . $curator->uid),
            l(t('restore'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/restore'),
            l(t('purge'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/delete'),
          )
        );
        #end row[]
      }
      else {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            format_date($entity->created),
            format_date($entity->changed),
            date('Y-m-d', $entity->dead_time),
            l($entity->customer_name, 'user/' . $customer_name->uid),
            l(t('restore'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/restore'),
            l(t('purge'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/delete'),
          )
        );
        #end row[]
      }
    }
  } #end foreach
  if (!empty($entity) && $user->name == $entity->curator  || in_array('administrator', $user->roles)) {
    $content = '';
    if (in_array('administrator', $user->roles)) {
      $content .= l(t('Purge all projects'), 'entity/brilliant_pr_project/basic/delete_all') . '<br>' .
        l(t('Restore all projects'), 'entity/brilliant_pr_project/basic/restore_all');
    }
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Deleted projects') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any removed projects.') .'</div>',
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
    $content = '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any removed projects.') .'</div>';
    $html = $content;
  }
  return ($html);
}
