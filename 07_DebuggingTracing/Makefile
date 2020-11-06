TEST_FILES = text.txt FIX_text.txt
GENERATES = fake_unlinkat.so $(TEST_FILES)

ALL: fake_unlinkat.so

fake_unlinkat.so : fake_unlinkat.c
	gcc -shared -fPIC fake_unlinkat.c -o fake_unlinkat.so -ldl

tests : fake_unlinkat.so
	touch $(TEST_FILES)
	rm $(TEST_FILES) && echo "exit code = $$?"
	touch $(TEST_FILES)
	-LD_PRELOAD=`pwd`/fake_unlinkat.so rm $(TEST_FILES) && echo "exit code = $$?"

clean :
	rm -rf $(GENERATES)