#!/usr/local/bin/bash

base="0.9"

# A subrevisão apontava para a árvore SVN. Agora migrada, segue as regras do GIT.
# ver="$base.`svnversion -n`"
# ver=${ver/[M|S]/}

ver=$base

sed -i -e "s/Versão .*/Versão $ver\<\/string>/" dialogs/aboutdialog.ui

echo "Versão $ver"

echo "Verificando string no arquivo xml: "
echo `cat dialogs/aboutdialog.ui | grep Versão`
