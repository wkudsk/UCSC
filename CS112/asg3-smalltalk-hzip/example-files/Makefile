MAIN_FILE = hzip.st 
TALK = gst -f $(MAIN_FILE)

all: test

test:
	$(TALK) -c test1.uniform.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test1.uniform.in
