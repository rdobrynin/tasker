
<?php
unset($form['field_first_name'][LANGUAGE_NONE][0]['value']['#title']);
unset($form['field_last_name'][LANGUAGE_NONE][0]['value']['#title']);
unset($form['field_phone'][LANGUAGE_NONE][0]['value']['#title']);
hide($form['actions']['submit']);
hide($form['actions']['cancel']);
?>

<div class="row-fluid">
  <div class="span8">
    <fieldset>
      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['field_first_name'][LANGUAGE_NONE]['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php
          print render($form['field_first_name'][LANGUAGE_NONE][0]['value']); ?>
        </div>
        <div class="col-lg-4 pull-left">
          <?php
          print render($form['field_last_name'][LANGUAGE_NONE][0]['value']); ?>
        </div>
      </div>
      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['field_phone'][LANGUAGE_NONE]['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['field_phone'][LANGUAGE_NONE][0]['value']); ?>
        </div>
      </div>

      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['field_company']['und']['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['field_company']); ?>
        </div>
      </div>

      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['account']['name']['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['account']['name']); ?>
        </div>
      </div>
      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['account']['current_pass']['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['account']['current_pass']); ?>
        </div>
      </div>
      <div class="row user_edit_profile">
        <div class="col-lg-2">
          <span class="field-title"><?php print render($form['account']['mail']['#title']); ?></span>
        </div>
        <div class="col-lg-4 pull-left">
          <?php print render($form['account']['mail']); ?>
        </div>
      </div>
      <div class="row user_edit_profile">
        <div class="col-lg-6">
          <span class="field-title"><?php print render($form['account']['pass']); ?></span>
        </div>
      </div>
      <?php  print drupal_render_children($form);?>
      <div class="row">
        <div class="col-lg-12 text-right">
          <span class="field-title"><?php print render($form['actions']['submit']); ?><?php print render($form['actions']['cancel']); ?></span>
        </div>
      </div>
    </fieldset>
  </div>
</div>

