<?php

/**
 * Callback function. here we prepare remove table for projects
 * @return array
 */

function brilliant_pr_task_remove_page() {
  global $user;
  $content = array();
  $content[] = array(
    '#type' => 'item',
    '#markup' => t('Hello') . ', ' . get_name($user->uid),
  );

// only Administrator can restore or delete all projects with status remove
  if (in_array('administrator', $user->roles)) {
    $content[] = array(
      '#type' => 'item',
      '#markup' => l(t('Purge all tasks'), 'entity/brilliant_pr_task/basic/delete_all'),
    );
    $content[] = array(
      '#type' => 'item',
      '#markup' => l(t('Restore all projects'), 'entity/brilliant_pr_task/basic/restore_all'),
    );
  }
  $content['table'] = brilliant_pr_task_remove_list_admin_entities();
  return $content;
}

/**
 *  Task remove admin list
 * @return array
 */

function brilliant_pr_task_remove_list_admin_entities() {
  $content = array();
  $entities = brilliant_pr_task_load_multiple(); // Defined above
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      global $user;
      if ($user->uid && $account = user_load($entity->uid)) {
        $user_name = $account->name;
        if ($entity->status == 5 && in_array('administrator', $user->roles) || $entity->status == 5 && $user->name == $entity->curator && in_array('curator', $user->roles)) {
          $rows[] = array(
            'data' => array(
              'id' => $entity->tid,
              'title' => l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
              'created' => format_date($entity->created),
              'dead_time' => date('Y-m-d', $entity->dead_time),
              'changed' => format_date($entity->changed),
              'total_time' => t('Total time spent'),
              'over_time' => t('Over time spent'),
              'author' => l($user_name, 'user/' . $entity->uid),
              'restore' => l(t('restore'), 'entity/brilliant_pr_task/basic/' . $entity->tid . '/restore'),
              'purge' => l(t('purge'), 'entity/brilliant_pr_task/basic/' . $entity->tid . '/delete'),
            ),
          );
        }
      }
      // Put our entities into a themed table.
      if ($entity->status == 5 && in_array('administrator', $user->roles) || $entity->status == 5 && $user->name == $entity->curator && in_array('curator', $user->roles)) {
        $content['entity_table'] = array(
          '#theme' => 'table',
          '#rows' => $rows,
          '#header' => array(
            t('ID#'),
            t('Title'),
            t('Created time'),
            t('Deadline date'),
            t('Finished time'),
            t('Total time'),
            t('Over time'),
            t('Author'),
            t('Restore'),
            t('Purge'),
          ),
        );
      }
    }
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' =>'<div class="alert alert-info a-message alert-dismissable"> '.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any completed project.') .'</div>',
    );
  }
  return $content;
}
