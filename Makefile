trojanized_quine.o: trojanized_quine.c
	clang -c -Wall -Wextra trojanized_quine.c

build_cemetery: append.c
	clang append.c -Wall -Wextra -o bury

change_gen_counter: gen_counter.c
	clang gen_counter.c -Wall -Wextra -o gen_counter

patricide: trojanized_quine.o build_cemetry gen_counter
	clang trojanized_quine.o -o trojanized_quine && ./bury trojanized_quine.c $(BRANCH) && ./trojanized_quine 2> trojanized_quine.c && ./gen_counter 2> gen_counter.c

inherit: trojanized_quine.o build_cemetry gen_counter
	clang trojanized_quine.o -o trojanized_quine && ./bury trojanized_quine.c collection_of_all_sins && ./trojanized_quine 2> trojanized_quine.c && ./gen_counter 2> gen_counter.c

visit_cemetery: fetch.c
	clang -Wall -Wextra fetch.c -o fetch && ./fetch $(GEN)
