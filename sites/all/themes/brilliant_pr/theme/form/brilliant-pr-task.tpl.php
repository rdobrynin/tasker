<?php
global $user;
global $base_url;
$form['opt_time']['date']['#title'] = 'Optimal date/time';
$form['dead_time']['date']['#title'] = 'Deadline date/time';
unset($form['dead_time']['time']['date']);
unset($form['opt_time']['time']['date']);
hide($form['submit']);
hide($form['remove']);
hide($form['cancel']);
hide($form['add_project']);
hide($form['back']);
if ($user->uid == in_array('customer', $user->roles)) {
  unset($form['implementor']);
}
global $user;

if (is_numeric(arg(3))) {
  $entity_id = arg(3);
  $task = brilliant_pr_task_load($tid = $entity_id);
  $changed_time = format_date($task->changed);
  $editor = user_load_by_name($task->editor);
}
?>
<div class="row-fluid">
  <div class="span8">
    <fieldset>
      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['title']['#title']); ?>&nbsp;<span class="required-note">*</span></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['title']); ?>
        </div>
        <!--add last edit time and editor-->
        <?php if(arg(4) == 'edit'):?>
        <div class="col-lg-6 pull-left">
          <span class="info_edit_project"><?php print t('Last edition'). ' ';?>
            <i style="font-weight:bold;">  <?php print($changed_time)?></i>&nbsp;by
          <?php  print l(get_name($editor->uid), 'user/' . $editor->uid); ?></div>
      </div>
      <?php endif; ?>
      </div>
<!--      check if we create task for this project, we hide project ref item-->
      <?php if (arg(3) == 'add' && is_null(arg(4)) ||$user->uid != in_array('customer', $user->roles) && arg(3) == 'add' && is_null(arg(4)) ): ?>
        <?php foreach ($form['ref'] as $item):?>
        <? endforeach?>
        <!--          if no project ref-->
          <?php if(empty($form['ref']['#options'])):?>
          <!-- Modal -->
          <div class="modal fade" id="modal_notask" data-backdrop="static" tabindex="-1" role="dialog" aria-labelledby="modal_notaskLabel" aria-hidden="true">
            <div class="modal-dialog">
              <div class="modal-content">
                <div class="modal-header">
                  <button type="button" disabled='disabled' class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                  <h4 class="modal-title"><?php print t('Add project');?></h4>
                </div>
                <div class="modal-body">
               <?php print t('You do not have any project to assign new task');?>
                </div>
                <div class="modal-footer">
                 <?php print render ($form['add_project']);?>
                 <?php print render ($form['back']);?>
                </div>
              </div><!-- /.modal-content -->
            </div><!-- /.modal-dialog -->
          </div><!-- /.modal -->
          <?php endif; ?>
        <div class="row">
          <div class="col-lg-2">
          <span class="field-title">
     <?php print render($form['ref']['#title']); ?>
            &nbsp;<span class="required-note">*</span></span>
          </div>

          <div class="col-lg-4 pull-left">
            <?php print render($form['ref']); ?>
          </div>
        </div>
      <?php endif; ?>
      <?php if (arg(4) == 'edit'): ?>
        <div class="row">
          <div class="col-lg-2">
          <span class="field-title">
     <?php print render($form['ref']['#title']); ?>
            &nbsp;<span class="required-note">*</span></span>
          </div>

          <div class="col-lg-4 pull-left">
            <?php print render($form['ref']); ?>
          </div>
        </div>
      <?php endif; ?>
<!--      curator field hide due to task belongs of current project -->
      <?php if ($user->uid != in_array('customer', $user->roles)): ?>
      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['curator']['#title']); ?>&nbsp;<span class="required-note">*</span></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['curator']); ?>
        </div>
      </div>
      <div class="row">
      <div class="col-lg-2">
          <span class="field-title">
            <?php print render($form['implementor']['#title']); ?>
            &nbsp;<span class="required-note">*</span></span>
      </div>
      <div class="col-lg-4 pull-left">
        <?php print render($form['implementor']); ?>
      </div>
  </div>
      <?php endif; ?>
      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['description']['#title']); ?></span>
        </div>
        <div class="col-lg-10 pull-left"  style="margin-bottom: 20px">
          <?php print render($form['description']); ?>
        </div>
      </div>
      <div class="division">
        <div class="row">
          <div class="col-lg-5">
            <span
              class="field-title"><?php print render($form['opt_time']); ?></span>
          </div>
        </div>
        <div class="row">
          <div class="col-lg-5">
            <span
              class="field-title"><?php print render($form['dead_time']); ?></span>
          </div>
        </div>
      </div>
      <?php
      if (!empty($form['status'][0]) || !empty($form['status'][1]) || !empty($form['status'][2]) || !empty($form['status'][3]) || !empty($form['status'][4]) || !empty($form['status'][5])) {
        print_r(' <div class="division">');
        print drupal_render_children($form);
        print_r('</div>');
      }
      else {
        print drupal_render_children($form);
      }
      ?>
      <div class="division">
        <div class="row">
          <div class="col-lg-12 text-right">
            <span class="field-title"><?php print render($form['submit']); ?>
              <a data-toggle="modal" href="#remove-task-btn"><?php print render($form['remove']); ?></a>
<?php print render($form['cancel']); ?></span>
          </div>
        </div>
      </div>
    </fieldset>
  </div>
</div>
<!-- Modal remove task -->
<div class="modal fade" id="remove-task-btn" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print t('Remove');?>&nbsp;<?php print render($form['title']['#value']); ?></h4>
      </div>
      <div class="modal-body">
        <?php print t('Are you sure remove this task ?');?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel');?></button>
        <?php print render($form['remove']); ?>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->

