AC_PREREQ([2.69])
AC_INIT(prog, 0.0.1, andrey.astapov@graphics.cs.msu.ru)
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([outlib.h])
AC_LANG(C)

# Checks for programs.
AC_PROG_CC

AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT

current_date=$(date)
data=$(echo AC_PACKAGE_NAME  "$PACKAGE_VERSION"  "$current_date")
src_files=$(find src/ -type f -name "*.c" -o -name "*.h")

for filename in $src_files
do
 	if [[ -z "$(grep COMMENT $filename)" ]]
	then
		sed -i -e "1 s/^/\x2F\x2A COMMENT: \"$data\" \x2A\x2F\n/;" $filename
	else
		sed -i "1 s/^.*COMMENT:.*/\x2F\x2A COMMENT: \"$data\" \x2A\x2F/;" $filename
	fi
done

echo "/* COMMENT: $data  */"