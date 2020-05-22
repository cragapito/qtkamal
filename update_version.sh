#!/usr/local/bin/bash

base="0.5"

ver="$base.`svnversion`"

sed -i -e "s/Versão .*/Versão $ver\<\/string>/" dialogs/aboutdialog.ui

echo "Versão $ver"

echo "Verificando string no arquivo xml: "
echo `cat dialogs/aboutdialog.ui | grep Versão`
