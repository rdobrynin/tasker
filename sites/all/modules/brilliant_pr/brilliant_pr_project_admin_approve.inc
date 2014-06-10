<?php

/**
 * Callback function. here we prepare approve table for projects
 */

function brilliant_pr_project_approve_page() {
  global $user;
  //Create a list of headers for Html table
  if (in_array('administrator', $user->roles)) {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer')),
      array('data' => t('Curator')),
      array('data' => t('Author')),
      array('data' => t('Author\'s email')),
    );
  }
  else {
    $header = array(
      array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
      array('data' => t('Title'), 'field' => 'title'),
      array('data' => t('Created'), 'field' => 'created'),
      array('data' => t('OPT'), 'field' => 'opt_time'),
      array('data' => t('DDT'), 'field' => 'dead_time'),
      array('data' => t('Customer')),
      array('data' => t('Author')),
      array('data' => t('Author\'s email')),
    );
  }
//Create the Sql query.
  $query = db_select('brilliant_pr_project', 'p')
    ->condition('status', '1', '=') //wait projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(5) //5 results per page
    ->extend('TableSort') //Sorting Extender
    ->orderByHeader($header)//Field to sort on is picked from $header
    ->fields('p', array(
      'pid',
      'title',
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
      $customer_name = user_load_by_name($entity->customer_name);
      $curator = user_load_by_name($entity->curator);
      $user_name = $account->uid;
      $user_mail = $account->mail;
      if (in_array('administrator', $user->roles)) {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            l(get_name($curator->uid), 'user/' . $curator->uid),
            l(get_name($user_name), 'user/' . $entity->uid),
            l($user_mail, 'mailto:' . $user_mail),
          )
        );
        #end row[]
      }
      elseif ($user->name == $entity->curator) {
        $rows[] = array(
          'data' => array(
            $entity->pid,
            l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
            format_date($entity->created),
            date('Y-m-d', $entity->opt_time),
            date('Y-m-d', $entity->dead_time),
            l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
            l(get_name($user_name), 'user/' . $entity->uid),
            l($user_mail, 'mailto:' . $user_mail),
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
          'caption' => '<h3>' . t('Projects for approve') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any projects for approve.') .'</div>',
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
    $content ='<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any projects for approve.') .'</div>';
    $html = $content;
  }
  return ($html);
}