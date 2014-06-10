<?php
$form['actions']['submit']["#attributes"]['class'][] = 'btn-success';
//hide($form['actions']['submit']);
$form['name']['#title'] = _bootstrap_icon('user') . ' ' . 'Username or e-mail address';
$form['actions']['submit']['#id'] = 'login_btn';
?>
    <div class="row">
      <div class="col-lg-6">
     <span class="grey">   <?php print render($form['name']); ?></span>
      </div>
      <div class="col-lg-6">
        <?php print drupal_render_children($form); ?>
      </div>

    </div>




