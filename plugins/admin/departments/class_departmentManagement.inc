<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2003  Cajus Pollmeier
  Copyright (C) 2011-2018  FusionDirectory

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

class departmentManagement extends management
{
  public static $skipSnapshots  = TRUE;

  public static function plInfo (): array
  {
    return [
      'plShortName'   => _('Departments'),
      'plTitle'       => _('Manage departments'),
      'plDescription' => _('Manage departments, countries, domain components, domains, localities and organization nodes,'),
      'plIcon'        => 'geticon.php?context=places&icon=folder&size=48',
      'plSection'     => ['accounts' => ['name' => _('Users and groups'), 'priority' => 0]],
      'plPriority'    => 0,
      'plManages'     => static::getDepartmentTypes(),

      'plProvidedAcls' => []
    ];
  }

  // Overriden save handler - We've to take care about the department tagging here.
  function saveChanges ()
  {
    $str = parent::saveChanges();
    if (!empty($str)) {
      return $str;
    }

    $this->refreshDeps();
  }

  function refreshDeps ()
  {
    global $config, $ui;
    $config->resetDepartmentCache();
    $ui->reset_acl_cache();
    $this->listing->refreshBasesList();
  }

  // Overridden remove request method - Avoid removal of the ldap base.
  public function removeRequested (array $action)
  {
    global $config;
    $action['targets'] = array_remove_entries([$config->current['BASE']], $action['targets']);
    return parent::removeRequested($action);
  }

  // Finally remove departments and update department browsers
  public function removeConfirmed (array $action)
  {
    parent::removeConfirmed($action);
    $this->refreshDeps();
  }

  static function getDepartmentTypes (): array
  {
    return ['DEPARTMENT','COUNTRY','DCOBJECT','DOMAIN','LOCALITY','ORGANIZATION'];
  }
}
