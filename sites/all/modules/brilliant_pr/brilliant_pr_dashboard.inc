<?
/**
 * GET PROJECTS STATS
 * @return string
 */

function get_project_statistics() {
  $result = '1';
  return $result;
}

/**
 * GET TASKS STATS
 * @return string
 */


function get_task_statistics() {
  $result = '2';
  return $result;
}

/**
 * GET LOGS
 * @return string
 */

function get_logs() {
  $result = '3';
  return $result;
}

/**
 * DASHBOARD RESULT DATA
 * @return string
 */

function brilliant_pr_project_dashboard_page() {
  global $user;
  $data = array(
    'page' => array(
      'username' => $user->name,
      'project_stats' => get_project_statistics(),
      'task_stats' => get_task_statistics(),
      'log_stats' => get_logs(),
    ),
  );
  $theme = 'brilliant_pr_dashboard';
  if (in_array('curator', $user->roles)) {
    $theme = 'brilliant_pr_dashboard_curator';
  }
  else {
    if (in_array('customer', $user->roles)) {
      $theme = 'brilliant_pr_dashboard_customer';
    }
    else {
      if (in_array('implementor', $user->roles)) {
        $theme = 'brilliant_pr_dashboard_implementor';
      }
    }
  }
  return theme($theme, $data);
}