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
$entities = brilliant_pr_project_load_multiple();
?>

<!-- get company taxonomy-->

<?php $vocab = taxonomy_vocabulary_machine_name_load('brilliant_pr_company_vocab'); ?>
<?php $company_tax = db_select('taxonomy_term_data', 't')
  ->condition('vid', $vocab->vid, '=')
  ->fields('t', array(
    'name',
  ));
$results_taxonomy = $company_tax
  ->execute();
?>

<?php foreach ($results_taxonomy as $tax): ?>
  <?php if (!empty($tax)): ?>
    <?php
    $query = db_select('brilliant_pr_project', 'p')
      ->condition('company', $tax->name, '=')
      ->fields('p', array(
        'pid',
        'title',
        'status',
        'created',
        'opt_time',
        'dead_time',
        'uid',
        'customer_name',
        'curator',
      ));
    $results = $query
      ->execute();
    $counter_projects = 0;
    $counter_projects_process = 0;
    $counter_projects_complete = 0;
    $counter_projects_approve = 0;
    $counter_projects_wait = 0;
    ?>
    <?php foreach ($results as $entity): ?>


      <?php if ($user->name == $entity->curator): ?>
        <?php $counter_projects++; ?>
      <?php endif; ?>

      <?php if ($user->name == $entity->curator && $entity->status == 2): ?>
        <?php $counter_projects_process++; ?>
      <?php endif; ?>

      <?php if ($user->name == $entity->curator && $entity->status == 3): ?>
        <?php $counter_projects_complete++; ?>
      <?php endif; ?>

      <?php if ($user->name == $entity->curator && $entity->status == 1): ?>
        <?php $counter_projects_approve++; ?>
      <?php endif; ?>

      <?php if ($user->name == $entity->curator && $entity->status == 0): ?>
        <?php $counter_projects_wait++; ?>
      <?php endif; ?>

    <?php endforeach; ?>
    <div class="client-wrapper col-md-3">
      <div class="client-box">
        <h4><?php print render($tax->name); ?></h4>

        <!--WAITING PROJECTS-->
        <div class="cl-label"><span
            class="label label-approve"><?php print t('Waiting projects'); ?></span>&nbsp;
          <span
            class="cl-title"><?php print render($counter_projects_wait); ?></span>
        </div>

        <!--CURRENT PROJECTS-->
        <div class="cl-label"><span
            class="label label-success"><?php print t('Current projects'); ?></span>&nbsp;
          <span
            class="cl-title"><?php print render($counter_projects_process); ?></span>
        </div>

        <!--COMPLETE PROJECTS-->
        <div class="cl-label"><span
            class="label label-info"><?php print t('Complete projects'); ?></span>&nbsp;
          <span
            class="cl-title"><?php print render($counter_projects_complete); ?></span>
        </div>

        <!--APPROVE PROJECTS-->
        <div class="cl-label"><span
            class="label label-danger"><?php print t('Approve projects'); ?></span>&nbsp;
          <span
            class="cl-title"><?php print render($counter_projects_approve); ?></span>
        </div>
      </div>
    </div>
  <?php endif; ?>
<?php endforeach; ?>



