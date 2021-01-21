#!/usr/local/bin/bash

base="0.8"

ver="$base.`svnversion -n`"

ver=${ver/[M|S]/}

sed -i -e "s/Versão .*/Versão $ver\<\/string>/" dialogs/aboutdialog.ui

echo "Versão $ver"

echo "Verificando string no arquivo xml: "
echo `cat dialogs/aboutdialog.ui | grep Versão`
