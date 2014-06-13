<?php
$form['actions']['submit']["#attributes"]['class'][] = 'btn-success';
$form['name']['#title'] = _bootstrap_icon('user') . ' ' . 'Username';
$form['pass']['#title'] = _bootstrap_icon('lock') . ' ' . 'Password';
$form['actions']['submit']['#id'] = 'login_btn';
?>
<div class="modal fade" id="login_modal"  data-keyboard="false" data-backdrop="static" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header window-login">
        <h4 class="modal-title"><?php print t('Login');?></h4>
      </div>
      <div class="modal-body">
        <div class="alert alert-block alert-danger messages error" id="login-error">
          <a class="close" data-dismiss="alert" href="#">×</a>
          <h4 class="element-invisible"><?php print t('Error message');?></h4>
          <?php print t('Sorry, unrecognized username or password');?><a href="/brilliant_pr/user/password?name=qws"><?php print t('Have you forgotten your password?');?></a></div>
        <div class="row">
          <div class="col-lg-6">
            <span class="grey"><?php print render($form['name']); ?></span>
          </div>
          <div class="col-lg-6">
            <span class="grey"><?php print render($form['pass']); ?></span>
          </div>
          <div class="col-lg-12">
            <?php print drupal_render_children($form); ?>
          </div>
        </div>
      </div>
      <div class="modal-footer" id="login_footer">
        <div style="float: left;"><a href="user/register"><?php print t('Create new account');?></a></div>
      <div style="float: right;"><a href="user/password"><?php print t('Request new password');?></a></div>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->