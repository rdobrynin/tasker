<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<?php
global $user;
$content = $element->content;
$content['implementor']['#title'] = t('Implementor');
$content['curator']['#title'] = t('Curator');
$content['customer_name']['#title'] = t('Contact person');
$content['opt_time']['#title'] = t('Optimal date');
$content['dead_time']['#title'] = t('Deadline date');
$content['description']['#title'] = t('Description');
$content['ref']['#title'] = t('Project ref');
//get implementor profile

if(!in_array('customer', $user->roles)) {
  $implementor_username = get_user_implementor($content['implementor']['#markup']);
  $implementor_fields = user_load_by_name($implementor_username);
}
//get customer profile
$customer_username = get_user_customer($content['customer_name']['#markup']);
$customer_fields = user_load_by_name($customer_username);
// get curator profile
$curator_username = get_user_curator($content['curator']['#markup']);
$curator_fields = user_load_by_name($curator_username);
?>
  <div class="row p-top user_edit_profile">
    <div class="col-lg-2">
      <span class="title_view"> <?php print render($content['description']['#title']); ?></span>
    </div>
    <div class="col-lg-10">
      <?php  print render($content['description']['#markup']); ?>
    </div>
  </div>
  <div class="row p-top user_edit_profile">
    <div class="col-lg-2">
      <span class="title_view"> <?php print render($content['ref']['#title']); ?></span>
    </div>
    <div class="col-lg-10">
      <?php  print render($content['ref']['#markup']); ?>
    </div>
  </div>
  <div class="user_edit_profile">
    <div class="row p-top">
      <div class="col-lg-2">
        <span class="title_view"> <?php  print render($content['company']['#title']); ?></span>
      </div>
      <div class="col-lg-6">
        <span class="glyphicon glyphicon-briefcase grey"></span>&nbsp;
        <?php  print render($content['company']['#markup']); ?>
      </div>
    </div>
    <!--customer-->
    <div class="row p-top">
      <div class="col-lg-2">
        <span class="title_view"><?php  print render($content['customer_name']['#title']); ?></span>
      </div>
      <div class="col-lg-2">
        <span class="grey">  <?php  print _bootstrap_icon('user'); ?></span>&nbsp;&nbsp;<?php  print render($content['customer_name']['#markup']); ?>
      </div>
      <div class="col-lg-3">
        <span class="grey">  <?php  print _bootstrap_icon('envelope'); ?></span>&nbsp;&nbsp;<?php  print $customer_fields->init; ?>
      </div>
      <div class="col-lg-2">
        <span class="grey">  <?php  print _bootstrap_icon('phone'); ?></span>&nbsp;&nbsp;<?php  print $customer_fields->field_phone[LANGUAGE_NONE][0]['value']; ?>
      </div>
      <div class="col-lg-1 text-left">
        <button class="btn btn-info wake-up"> <?php  print _bootstrap_icon('volume-up'); ?>  <span>&nbsp;</span> <?php print t('Wake up call')?></button>
      </div>
    </div>

    <?php if(!in_array('customer', $user->roles)):?>
    <!--implementor-->
    <div class="row p-top">
      <div class="col-lg-2">
        <span class="title_view"><?php  print render($content['implementor']['#title']); ?></span>
      </div>
      <div class="col-lg-2">
        <span class="grey">  <?php  print _bootstrap_icon('user'); ?></span>&nbsp;&nbsp;<?php  print render($content['implementor']['#markup']); ?>
      </div>
      <div class="col-lg-3">
        <span class="grey">  <?php  print _bootstrap_icon('envelope'); ?></span>&nbsp;&nbsp;<?php  print $implementor_fields->init; ?>
      </div>
      <div class="col-lg-2">
        <span class="grey">  <?php  print _bootstrap_icon('phone'); ?></span>&nbsp;&nbsp;<?php  print $implementor_fields->field_phone[LANGUAGE_NONE][0]['value']; ?>
      </div>
      <div class="col-lg-1 text-left">
        <button class="btn btn-info wake-up"> <?php  print _bootstrap_icon('bullhorn'); ?>  <span>&nbsp;</span> <?php print t('Call for report')?></button>
      </div>
    </div>

    <?php endif?>


    <!--  curator-->
    <div class="row p-top">
      <div class="col-lg-2">
        <span class="title_view"> <?php  print render($content['curator']['#title']); ?></span>
      </div>
      <div class="col-lg-2">
        <span class="grey"><?php  print _bootstrap_icon('user'); ?></span>&nbsp;&nbsp;<?php  print render($content['curator']['#markup']); ?>
      </div>
      <div class="col-lg-3">
        <span class="grey">  <?php  print _bootstrap_icon('envelope'); ?></span>&nbsp;&nbsp;<?php  print $curator_fields->init; ?>
      </div>
      <div class="col-lg-2">
        <span class="grey">  <?php  print _bootstrap_icon('phone'); ?></span>&nbsp;&nbsp;<?php  print $curator_fields->field_phone[LANGUAGE_NONE][0]['value']; ?>
      </div>
      <div class="col-lg-1 text-left">
        <button class="btn btn-info wake-up"> <?php  print _bootstrap_icon('volume-up'); ?>  <span>&nbsp;</span> <?php print t('Wake up call')?></button>
      </div>
    </div>
  </div>
  <div class="row">
    <div class="col-lg-2">
      <span class="title_view"> <?php  print render($content['opt_time']['#title']); ?></span>
      <br>
      <?php  print render($content['opt_time']['#markup']); ?>
    </div>
    <div class="col-lg-2">
      <span class="title_view"> <?php  print render($content['dead_time']['#title']); ?></span>
      <br>
      <?php  print render($content['dead_time']['#markup']); ?>
    </div>

    <div class="col-lg-2">
      <span class="title_view"> <?php  print render($content['status']['#title']); ?><span class="badge status-badge">!</span></span>
      <br>
      <?php  print render($content['status']['#markup']); ?>
    </div>
    <div class="col-lg-2">
      <span class="title_view"> <?php  print render($content['created']['#title']); ?></span>
      <br>
      <?php  print render($content['created']['#markup']); ?>
    </div>
    <div class="col-lg-2">
      <span class="title_view"> <?php  print render($content['changed']['#title']); ?></span
      <br>
      <?php  print render($content['changed']['#markup']); ?>
    </div>
  </div>
<?php //print drupal_render_children($content); ?>