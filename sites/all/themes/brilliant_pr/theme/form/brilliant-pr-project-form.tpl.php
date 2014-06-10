
<?php
global $user;
$form['opt_time']['date']['#title'] = 'Optimal date/time';
$form['dead_time']['date']['#title'] = 'Deadline date/time';
hide($form['submit']);
hide($form['submit_task']);
hide($form['delete']);
hide($form['cancel']);
hide($form['remove']);
// get changed time
if (is_numeric(arg(3))) {
  $entity_id = arg(3);
  $project = brilliant_pr_project_load($pid = $entity_id);
  $changed_time = format_date($project->changed);
  $curator = user_load_by_name($project->curator);
  $editor = user_load_by_name($project->editor);
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
      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['description']['#title']); ?>&nbsp;<span class="required-note">*</span></span>
        </div>
        <div class="col-lg-10 pull-left"  style="margin-bottom: 20px">
          <?php print render($form['description']); ?>
        </div>
      </div>
      <div class="division">
      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['company']['#title']); ?>&nbsp;<span class="required-note">*</span></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['company']); ?>
          <div class="help"><?php print t('Start typing the company name, if it is in our data base, the window assign you. To create a new client,
enter the company name. Once all the fields are filled in, save the project. The client will be added to our database.');?></div>
        </div>
      </div>

      <div class="row">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['customer_name']['#title']); ?>&nbsp;<span class="required-note">*</span></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['customer_name']); ?>
        </div>
      </div>
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
            <button class="btn btn-success" disabled="disabled"><?php print t('Add new contact person')?></button>
          </div>

        </div>
      </div> <!--   end of division   -->


      <div class="division">
        <div class="row">
          <div class="col-lg-3">
            <span
              class="field-title"><?php print render($form['opt_time']); ?></span>
          </div>
          <div class="col-lg-3">
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
            <span class="field-title"><?php print render($form['submit']); ?><?php print render($form['submit_task']); ?>
              <a data-toggle="modal" href="#remove-project-btn"><?php print render($form['remove']); ?>
              <a data-toggle="modal" href="#delete-project-btn"><?php print render($form['delete']); ?></a><?php print render($form['cancel']); ?></span>
          </div>
        </div>
      </div>
    </fieldset>
  </div>
</div>
<!-- Modal delete project -->
<div class="modal fade" id="delete-project-btn" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print t('Delete');?>&nbsp;<?php print render($form['title']['#value']); ?></h4>
      </div>
      <div class="modal-body">
       <?php print t('Are you sure delete this project ?');?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel');?></button>
        <?php print render($form['delete']); ?>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->
<!-- Modal delete project -->
<div class="modal fade" id="remove-project-btn" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print t('Remove');?>&nbsp;<?php print render($form['title']['#value']); ?></h4>
      </div>
      <div class="modal-body">
        <?php print t('Are you sure remove this project ?');?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel');?></button>
        <?php print render($form['remove']); ?>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->