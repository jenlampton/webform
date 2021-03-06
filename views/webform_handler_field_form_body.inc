<?php

/**
 * Views handler to display the content of a webform form.
 *
 * Field handler to present the Webform form body to the user.
 */
class webform_handler_field_form_body extends views_handler_field {

  /**
   *
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
  }

  /**
   *
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['label'] = array('default' => 'Form', 'translatable' => TRUE);
    return $options;
  }

  /**
   *
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   *
   */
  public function render($values) {
    $node = node_load($values->{$this->aliases['nid']});

    if (node_access('view', $node)) {
      // Populate $node->content['webform'] by reference.
      webform_node_view($node, 'form');
      $form_body = isset($node->content['webform']) ? backdrop_render($node->content['webform']) : NULL;
    }
    else {
      return;
    }

    return $form_body;
  }

}
