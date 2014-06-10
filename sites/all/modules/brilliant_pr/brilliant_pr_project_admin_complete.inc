<?php
/**
 * project admin complete list
 * @return array
 */

function brilliant_pr_project_complete_page() {
  global $user;
  //Create a list of headers for Html table
  $header = array(
    array('data' => t('ID'), 'field' => 'pid', 'sort' => 'asc'),
    array('data' => t('Title'), 'field' => 'title'),
    array('data' => t('Created'), 'field' => 'created'),
    array('data' => t('Changed'), 'field' => 'changed'),
    array('data' => t('OPT'), 'field' => 'opt_time'),
    array('data' => t('DDT'), 'field' => 'dead_time'),
    array('data' => t('Total time spent')),
    array('data' => t('Customer')),
    array('data' => t('Delete project')),
  );
//Create the Sql query.
  $query = db_select('brilliant_pr_project', 'p')
    ->condition('status', 3) //Only completed projects
    ->extend('PagerDefault') //Pager Extender
    ->limit(5) //5 results per page
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
    if ($user->name == $entity->curator || in_array('administrator', $user->roles)) {
      $customer_name = user_load_by_name($entity->customer_name);
      $rows[] = array(
        'data' => array(
          $entity->pid,
          l($entity->title, 'entity/brilliant_pr_project/basic/' . $entity->pid),
          format_date($entity->created),
          format_date($entity->changed),
          date('Y-m-d', $entity->opt_time),
          date('Y-m-d', $entity->dead_time),
          getTheTime($entity->changed, $entity->created),
          l(get_name($customer_name->uid), 'user/' . $customer_name->uid),
          l(t('delete'), 'entity/brilliant_pr_project/basic/' . $entity->pid . '/remove'),
        )
      );
    }
  } #end foreach

  if (!empty($entity)) {
    $content = '';
    $html = $content . theme('table',
        array(
          'header' => $header,
          'rows' => $rows,
          'caption' => '<h3>' . t('Completed projects') . '</h3>',
          //Optional Caption for the table
          'sticky' => TRUE,
          //Optional to indicate whether the table headers should be sticky
          'empty' => t('Not found any completed project.'),
          //Optional empty text for the table if resul tset is empty
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

/**
 * Implements getTime function for calculating hours and minutes
 * @param $time_end
 * @param $time_start
 * @return bool|string
 */

function getTheTime($time_end, $time_start) {
  $seconds = $time_end - $time_start;
// return value
  $ret = "";
// get the hours
  $hours = intval(intval($seconds) / 3600);
  if ($hours > 0) {
    $ret .= "$hours " . t("hours ");
  }
// get the minutes
  $minutes = bcmod((intval($seconds) / 60), 60);
  if ($minutes >= 1) {
    $minutes = intval($minutes) + 1; // we have at least some seconds, then we add 1 minute to common value
  }
  else {
//    // get the seconds
//    $seconds = bcmod(intval($seconds), 60);
//    $ret .= "$seconds " . t("seconds");
    return TRUE;
  }
  if ($hours > 0 || $minutes > 0) {
    $ret .= "$minutes " . t("minutes ");
  }
  return $ret;
}