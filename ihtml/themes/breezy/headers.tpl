<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" {if $lang}lang="{$lang}" xml:lang="{$lang}"{/if} {if $rtl}dir="rtl" class="rtl"{else}class="ltr"{/if}>

<head>
  <title>FusionDirectory{if isset($title)} - {$title|escape}{elseif isset($headline)} - {$headline|escape}{/if}</title>

  <meta charset="utf-8"/>

  <meta name="description" content="FusionDirectory - Your Infrastructure Manager"/>
  <meta name="author" lang="en" content="FusionDirectory Project"/>
  <meta name="viewport" content="width=device-width"/>

  {include file={filePath file="css.tpl"}}
  <link rel="stylesheet" type="text/css" href="{filePath file="printer.css"}" media="print"/>

  <link rel="shortcut icon" href="favicon.ico"/>

  <script src="include/prototype.js" type="text/javascript"></script>
  <script src="include/fusiondirectory.js" type="text/javascript"></script>
{if $usePrototype == 'true'}
  <script src="include/scriptaculous.js" type="text/javascript"></script>
  <script src="include/builder.js" type="text/javascript"></script>
  <script src="include/effects.js" type="text/javascript"></script>
  <script src="include/dragdrop.js" type="text/javascript"></script>
  <script src="include/controls.js" type="text/javascript"></script>
  <script src="include/pulldown.js" type="text/javascript"></script>
{/if}
  <script src="include/tsorter.js" type="text/javascript"></script>
{foreach from=$js_files item=file}
  <script src="{$file}" type="text/javascript"></script>
{/foreach}
</head>

