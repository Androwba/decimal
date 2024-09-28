CC                =      gcc
CFLAGS            =     -std=c11 -Wall -Wextra -Werror
LINUX_FLAGS       =     -lsubunit -lrt -lpthread -lm -D_GNU_SOURCE
LCHECK            =     -lcheck -lgmp
GCFLAGS           =     -fprofile-arcs -ftest-coverage
LDFLAGS           =     -fprofile-arcs --coverage
RM                =      rm -rf
UNITNAME          =      unit_test
GENHTML-DIRECTORY =    --output-directory report
ARCHIVER          =      ar
ARFLAGS           =      cr -s
FIND&CHECK        =      $(wildcard *.c *.h \
	/s21_bits/*.c ./s21_another/*.c \
	./s21_comparison/*.c ./s21_convertion/*.c \
	./s21_arithmetic/*.c)
SOURCES          :=      s21_bits/bit.c \
						s21_bits/sign.c \
						s21_bits/shift.c \
						s21_bits/exponent.c \
						s21_bits/decimal.c \
						s21_another/s21_floor.c \
						s21_another/s21_truncate.c \
						s21_another/balancing.c \
						s21_another/bank_rnd.c \
						s21_another/s21_neg.c \
						s21_another/s21_round.c \
						s21_comparison/s21_eq.c \
						s21_comparison/s21_less.c \
						s21_comparison/s21_gr.c \
						s21_comparison/s21_gr_or_eq.c \
						s21_comparison/s21_not_eq.c \
						s21_comparison/s21_less_or_eq.c \
						s21_convertion/int_to_dec.c \
						s21_convertion/float_to_dec.c \
						s21_convertion/dec_to_float.c \
						s21_convertion/dec_to_int.c \
						s21_convertion/shared.c \
						s21_arithmetic/add.c \
						s21_arithmetic/sub.c \
						s21_arithmetic/mul.c \
						s21_arithmetic/div.c \
						s21_arithmetic/fmod.c \

OBJ_DIR          := ./obj
OBJ_GCOV_DIR     := ./obj_gcov
OBJECTS          := $(addprefix obj/,$(SOURCES:.c=.o))
OBJECTS_GCOV     := $(addprefix obj_gcov/,$(SOURCES:.c=.o))

ifeq ($(shell uname), Linux)
LCHECK += $(LINUX_FLAGS)
OPEN = xdg-open report/index.html
LEAKS = CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s
else
OPEN = open report/index.html
LEAKS = @CK_FORK=no leaks --atExit --
endif

all: s21_decimal.a

s21_decimal.a: create_dir $(OBJECTS)
	$(ARCHIVER) $(ARFLAGS) $@ $(OBJ_DIR)/*.o

lib_gcov.a: create_dir $(OBJECTS_GCOV)
	$(ARCHIVER) $(ARFLAGS) $@ $(OBJ_GCOV_DIR)/*.o

create_dir:
	mkdir -p $(OBJ_DIR) $(OBJ_GCOV_DIR)

test: unit_test.c s21_decimal.h lib_gcov.a
	$(CC) $(CFLAGS) $^ -o $(UNITNAME) $(LCHECK) $(LDFLAGS) $(GCFLAGS)
	./$(UNITNAME)
	@mv *gcda *gcno $(OBJ_GCOV_DIR)/

gcov_report: clean test
	@rm -f $(OBJ_GCOV_DIR)/*tests*
	@lcov -c -d $(OBJ_GCOV_DIR)/. -o $(OBJ_GCOV_DIR)/coverage.info
	@genhtml $(OBJ_GCOV_DIR)/coverage.info $(GENHTML-DIRECTORY)
	@$(OPEN)

$(OBJ_DIR)/%.o: %.c s21_decimal.h
	@$(CC) $(CFLAGS) -c $< -o $(subst /,_,$@) $(LINUX_FLAGS)
	@mv *.o $(OBJ_DIR)/

$(OBJ_GCOV_DIR)/%.o: %.c s21_decimal.h
	@$(CC) $(CFLAGS) $(GCFLAGS) -c $< -o $(subst /,_,$@) $(LINUX_FLAGS)
	@mv *.o *gcno $(OBJ_GCOV_DIR)/

cpp:
	@echo "\033[92m◄----------------------- CPP ------------------------------►\033[0m"
	@cppcheck --enable=all --suppress=missingIncludeSystem $(FIND&CHECK)

style:	
	@echo "\033[96m◄----------------------- Style Test -----------------------►\033[0m"
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c $(FIND&CHECK) 
	
leaks:
	@echo "\033[92m◄----------------------- Leaks ----------------------------►\033[0m"
	$(LEAKS) ./$(UNITNAME)

clean:
	$(RM) $(OBJ_DIR) $(OBJ_GCOV_DIR)
	$(RM) s21_decimal.a lib_gcov.a
	$(RM) *.o *gc* *.dSYM unit_test
	$(RM) report
	$(RM) CPPLINT.cfg

.PHONY: rebuild 
rebuild:
	$(MAKE) clean
	$(MAKE) all 

# make git m="your message"
git:
	git add .
	git commit -m "$m"
	git push origin develop