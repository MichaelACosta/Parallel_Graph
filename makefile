include Makefile.in

.PHONY: clean

OBJFILES = $(OBJ_DIR)/graph.o $(OBJ_DIR)/main.o $(OBJ_DIR)/graphmutex.o $(OBJ_DIR)/graphmutexgg.o $(OBJ_DIR)/graphatomic.o $(OBJ_DIR)/graphstm.o


all: $(OBJ_DIR)/graph.out

$(OBJ_DIR)/graph.out: $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o $@ $^  $(LDFLAGS)
	cp $(OBJ_DIR)/graph.out .


$(OBJ_DIR)/graphstm.o: ${SRC_DIR}/graphstm.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/graphstm.cpp $(CPPFLAGS) -c -o $@

$(OBJ_DIR)/graphatomic.o: ${SRC_DIR}/graphatomic.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/graphatomic.cpp $(CPPFLAGS) -c -o $@

$(OBJ_DIR)/graphmutex.o: ${SRC_DIR}/graphmutex.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/graphmutex.cpp $(CPPFLAGS) -c -o $@

$(OBJ_DIR)/graphmutexgg.o: ${SRC_DIR}/graphmutexgg.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/graphmutexgg.cpp $(CPPFLAGS) -c -o $@

$(OBJ_DIR)/graph.o: ${SRC_DIR}/graph.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/graph.cpp $(CPPFLAGS) $(D) -c -o $@

$(OBJ_DIR)/main.o: ${SRC_DIR}/main.cpp
	mkdir -p $(OBJ_DIR)
	$(CPP) ${SRC_DIR}/main.cpp $(CPPFLAGS) -c -o $@


clean:
	rm -r $(TARGET_DIR) graph.out
