<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2007  Fabian Hickert
  Copyright (C) 2011-2016  FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

class setupStepWelcome extends setupStep
{
  var $header_image = 'geticon.php?context=applications&icon=config-welcome&size=48';

  static function getAttributesInfo (): array
  {
    return [
      'welcome' => [
        'name'      => _('Welcome'),
        'template'  => get_template_path("setup_welcome.tpl", TRUE, dirname(__FILE__)),
        'attrs'     => [
        ]
      ]
    ];
  }

  function __construct ($parent)
  {
    parent::__construct($parent);

    $this->is_enabled     = TRUE;
    $this->is_active      = TRUE;
    $this->authPath       = CACHE_DIR.'fusiondirectory.auth';
  }

  /* We need to init them with a method to be able to use _() */
  function update_strings ()
  {
    $this->s_short_name   = _('Welcome');
    $this->s_title        = _('Welcome to FusionDirectory setup wizard');
    $this->s_description  = _('The welcome message');
  }

  function execute (): string
  {
    $smarty = get_smarty();
    $smarty->assign('auth_id', session_id());

    $smarty->assign('path', $this->authPath);
    return parent::execute();
  }

  function save_object ()
  {
    parent::save_object();
    $id = "";

    /* Get auth ID from file */
    if (file_exists($this->authPath) && is_readable($this->authPath)) {
      $contents = file($this->authPath);
      $id       = chop($contents[0]);
    }

    /* Continue if we've the correct ID */
    if ($id == session_id()) {
      $this->is_completed = TRUE;
    } else {
      $this->is_completed = FALSE;
    }
  }
}
