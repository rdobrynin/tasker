<?php
//global $user;
//if($user->uid == in_array('curator', $user->roles)) {
//  print_r('curator');
//}
//elseif($user->uid == in_array('administrator', $user->roles)) {
//  print_r('admin');
//}

$form['actions']['submit']["#attributes"]['class'][] = 'btn-success btn-max';
hide($form['actions']['submit']);

?>
     <div class="row p-top">
       <div class="col-lg-6">
         <?php print render($form['field_first_name'][LANGUAGE_NONE][0]['value']); ?>
       </div>
       <div class="col-lg-6">
         <?php print render($form['field_last_name'][LANGUAGE_NONE][0]['value']); ?>
       </div>
     </div>
     <div class="row p-top">
       <div class="col-lg-6">
         <?php print render($form['field_company']); ?>
       </div>
       <div class="col-lg-6">
         <?php print render($form['field_phone'][LANGUAGE_NONE][0]['value']); ?>
       </div>
     </div>



    <div class="row p-top">
      <div class="col-lg-6">
        <?php print render($form['account']['name']); ?>
      </div>
    </div>

<div class="row p-top">
  <div class="col-lg-6">
    <?php print render($form['account']['mail']); ?>
  </div>
</div>

     <div class="row p-top">
       <div class="col-lg-6">
         <?php print render($form['account']['pass']['pass1']); ?>
       </div>
       <div class="col-lg-6">
         <?php print render($form['account']['pass']['pass2']); ?>
       </div>
     </div>
  <div class="row p-top">
    <div class="col-lg-6">
      <?php print render($form['account']['roles']); ?>
    </div>
    <div class="col-lg-6">
      <?php print render($form['account']['status']); ?>
    </div>
  </div>
<?php print drupal_render_children($form); ?>
  <div class="row p-top">
    <div class="col-lg-12 text-center">
      <?php print render(  $form['actions']['submit']); ?>
    </div>
  </div>