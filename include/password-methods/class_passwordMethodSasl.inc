<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2011-2019  FusionDirectory

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
  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/*!
 * \file class_passwordMethodSasl.inc
 * Source code for class passwordMethodSasl
 */

/*!
 * \brief This class contains all the functions for sasl password method
 * \see passwordMethod
 */
class passwordMethodSasl extends passwordMethod
{
  // uid, or exop specified field value
  var $uid    = '';
  var $realm  = '';
  var $exop   = '';

  /*!
   * \brief passwordMethodSasl Constructor
   *
   * \param string $dn The DN
   * \param object $userTab The user main tab object
   */
  function __construct ($dn = '', $userTab = NULL)
  {
    global $config;
    $this->realm  = trim($config->get_cfg_value('saslRealm', ''));
    $this->exop   = trim($config->get_cfg_value('saslExop', ''));

    if ($dn == '' || $dn == 'new') {
      return;
    }

    $attr = (empty($this->exop) ? 'uid' : $this->exop);

    if (($userTab !== NULL) && isset($userTab->$attr)) {
      $this->uid = $userTab->$attr;
    } else {
      $ldap = $config->get_ldap_link();
      $ldap->cd($config->current['BASE']);
      $ldap->cat($dn, [$attr]);
      if ($ldap->count() == 1) {
        $attrs = $ldap->fetch();
        $this->uid = $attrs[$attr][0];
      } else {
        $error = new FusionDirectoryError(htmlescape(sprintf(_('Cannot change password, unknown user "%s"'), $dn)));
        $error->display();
      }
    }
  }

  /*!
   * \brief Is available
   *
   * \return TRUE if is avaibable
   */
  public function is_available (): bool
  {
    if (empty($this->realm) && empty($this->exop)) {
      return FALSE;
    }
    return TRUE;
  }

  /*!
   * \brief Generate template hash
   *
   * \param string $pwd Password
   * \param bool $locked Should the password be locked
   *
   * \return string the password hash
   */
  public function generate_hash (string $pwd, bool $locked = FALSE): string
  {
    if (empty($this->exop)) {
      if (empty($this->realm)) {
        $error = new FusionDirectoryError(htmlescape(_('You need to fill saslRealm or saslExop in the configuration screen in order to use SASL')));
        $error->display();
      }
      return '{SASL}'.($locked ? '!' : '').$this->uid.'@'.$this->realm;
    } else {
      // may not be the uid, see saslExop option
      return '{SASL}'.($locked ? '!' : '').$this->uid;
    }
  }

  function checkPassword ($pwd, $hash): bool
  {
    // We do not store passwords, can’t know if they’re the same
    return FALSE;
  }

  /*!
   * \brief Get the hash name
   */
  static function get_hash_name ()
  {
    return 'sasl';
  }

  /*!
   * \brief Password needed
   *
   * \return boolean
   */
  function need_password (): bool
  {
    global $config;
    return ($config->get_cfg_value('forceSaslPasswordAsk', 'FALSE') == 'TRUE');
  }
}
