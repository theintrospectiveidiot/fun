trojanized_quine.o: trojanized_quine.c
	gcc -c trojanized_quine.c

build_cemetery: append.c
	gcc append.c -o append

change_gen_counter: gen_counter.c
	gcc gen_counter.c -o gen_counter

patricide: trojanized_quine.o append gen_counter
	gcc trojanized_quine.o -o trojanized_quine && ./append trojanized_quine.c $(BRANCH) && ./trojanized_quine 2> trojanized_quine.c && ./gen_counter 2> gen_counter.c

inherit: trojanized_quine.o append gen_counter
	gcc trojanized_quine.o -o trojanized_quine && ./append trojanized_quine.c collection_of_all_sins && ./trojanized_quine 2> trojanized_quine.c && ./gen_counter 2> gen_counter.c

visit_cemetery: fetch.c
	gcc fetch.c -o fetch && ./fetch $(GEN)
