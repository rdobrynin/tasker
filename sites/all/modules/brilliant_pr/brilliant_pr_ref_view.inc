<?php

/**
 * Task referenced page
 * @return array
 */

function brilliant_pr_ref_view($view_mode = 'tid') {

  $content = array(
    '#view_mode' => $view_mode,
  );

  $content[] = array(
    '#type' => 'item',
    '#markup' => l(t(''), ''),
  );

  $content['table'] = brilliant_pr_task_ref_list_admin_entities();
  return $content;
}

/**
 * Load tasks per one project
 * @return array
 */

function  brilliant_pr_task_ref_list_admin_entities() {
  $content = array();
  $curr_project = arg(3); //get current #ID form path
  $project_entity = brilliant_pr_project_load($pid = $curr_project);
  $entities = brilliant_pr_task_load_multiple(); // Defined above
  $counter = 0; // make counter in cycle
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      if ($entity->status != 5) {
        global $user;
        if ($user->uid && $account = user_load($entity->uid)) {
          $user_name = $account->name;
          $user_mail = $account->mail;
          if ($entity->ref == $project_entity->pid && $user->name == $project_entity->curator || $entity->ref == $project_entity->pid && $user->uid == in_array('administrator', $user->roles)
            || $entity->ref == $project_entity->pid && $user->name == $project_entity->customer_name
          ) {
            $counter++;
            $rows[] = array(
              'data' => array(
                'id' => $entity->tid,
                'title' => l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
                'status' => brilliant_pr_task_status_position_title($entity->status),
                'curr-time' => '-',
                'created' => format_date($entity->created),
                'changed' => format_date($entity->changed),
                'dead_time' => date('Y-m-d H:i:s', $entity->dead_time),
                'author' => l($user_name, 'user/' . $entity->uid),
                'author_mail' => l($user_mail, 'mailto:' . $user_mail),
                'edit' => l('edit', 'entity/brilliant_pr_task/basic/' . $entity->tid . '/edit'),
              ),
            );
          }
        }
        // Put our entities into a themed table.
        if ($entity->ref == $project_entity->pid && $user->name == $project_entity->curator || $entity->ref == $project_entity->pid && $user->uid == in_array('administrator', $user->roles)
          || $entity->ref == $project_entity->pid && $user->name == $project_entity->customer_name
        ) {
          $content['entity_table'] = array(
            '#theme' => 'table',
            '#rows' => $rows,
            '#header' => array(
              t('ID#'),
              t('Task title'),
              t('Task status'),
              t('CTS'),
              t('Created time'),
              t('Last change'),
              t('Deadline time'),
              t('Author'),
              t('Author\'s email'),
              t('Edit')
            ),
          );
        }
      }
    }
  }
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any tasks.') .'</div>',
    );
  }
  return $content;
}