MAIN_FILE = hzip.st 
TALK = gst -f $(MAIN_FILE)

all: test testall

test:
	$(TALK) -c test1.uniform.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test1.uniform.in
testall:
	$(TALK) -c test3.gif.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test3.gif.in
	$(TALK) -c test4.aaaaaaaa.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test4.aaaaaaaa.in
	$(TALK) -c test5.ps.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test5.ps.in
	$(TALK) -c test6.huffman.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test6.huffman.in
	$(TALK) -c test7.etaoin.in test1.out
	$(TALK) -u test1.out test1.expected
	diff test1.expected test7.etaoin.in
	$(TALK) -c William_Shakespeare.txt Shake.out
	$(TALK) -u Shake.out Reconstructed.out
	diff Reconstructed.out William_Shakespeare.txt
	