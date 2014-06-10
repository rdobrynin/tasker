<?php
/**
 * Provide a list of task existing entities and the ability to add more.
 * Tabs provide field and display admin management.
 */

function brilliant_pr_task_admin_page() {
  global $user;
  $content = array();

  // task_list_entities() defined below returns a 'theme array' with #theme => 'table'
  $content['table'] = brilliant_pr_task_list_admin_entities();
  return $content;
}

/**
 * list admin task entities
 * @return array
 */

function brilliant_pr_task_list_admin_entities() {
  $content = array();
  $entities = brilliant_pr_task_load_multiple(); // Defined above
  if (!empty($entities)) {
    foreach ($entities as $entity) {
      $project_entity = brilliant_pr_project_load($pid = $entity->ref);
      if ($entity->status != 5) {
        global $user;
        if ($user->uid && $account = user_load($entity->uid)) {
          $user_name = $account->uid;
          $user_mail = $account->mail;
          if ($entity->status != 1 && $entity->status != 0 && $user->name == $entity->curator || $entity->status != 1 && $entity->status != 0 && in_array('administrator', $user->roles)) {
            $rows[] = array(
              'data' => array(
                'id' => $entity->tid,
                'title' => l($entity->title, 'entity/brilliant_pr_task/basic/' . $entity->tid),
                'status' => brilliant_pr_task_status_position_title($entity->status),
                'project_title' => isset($project_entity->pid) ? l($project_entity->title, 'entity/brilliant_pr_project/basic/' . $project_entity->pid) : '-',
                'curr-time' => '-',
                'created' => format_date($entity->created),
                'changed' => format_date($entity->changed),
                'dead_time' => date('Y-m-d H:i:s', $entity->dead_time),
                'author' => l(get_name($user_name), 'user/' . $entity->uid),
                'author_mail' => l($user_mail, 'mailto:' . $user_mail),
                'edit' => ($entity->status == 1) ? l(t('completed'), 'admin/structure/brilliant_pr_task/manage/complete') :
                    l('edit', 'entity/brilliant_pr_task/basic/' . $entity->tid . '/edit'),
              ),
            );
          }
        }
        // Put our entities into a themed table.
        if ($entity->status != 1 && $entity->status != 0 && $user->name == $entity->curator || $entity->status != 1 && $entity->status != 0 && in_array('administrator', $user->roles)) {
          $content['entity_table'] = array(
            '#theme' => 'table',
            '#rows' => $rows,
            '#header' => array(
              t('ID#'),
              t('Task\'s name'),
              t('CTS'),
              t('Project ref'),
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
      } #end if with status 5
    } #end foreach
  } #end if
  else {
    // There were no entities. Tell the user.
    $content[] = array(
      '#type' => 'item',
      '#markup' => '<div class="alert alert-info a-message alert-dismissable">'.'<button type="button" class="close" data-dismiss="alert" aria-hidden="true">&times;</button>'.t('Not found any current tasks.') .'</div>',
    );
  }
  return $content;
}