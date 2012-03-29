CXX = g++
CXXFLAGS = -c -Wall -O3  -fpermissive -ggdb $(INCLUDE) 
LDFLAGS = -lm -ltinyxml
INCLUDE = -I./include/
BUILD = ./build
EXECNAME = raytracer

OBJSCRUDE = Vector.o Ray.o Triangle.o BBox.o Bvh.o main.o RayTracer.o xmlExporter.o

OBJS = $(addprefix $(BUILD)/, $(OBJSCRUDE))

all: $(EXECNAME)

$(EXECNAME): $(OBJS) 
	$(CXX) $(OBJS) -o $(BUILD)/$(EXECNAME) $(LDFLAGS) -I./include/

$(BUILD)/%.o: src/%.cpp include/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
$(BUILD)/%.o: src/%.cpp 
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	rm -f $(BUILD)/*.o $(SRC)/*~ ./include/*~ ./*~ $(BUILD)/raytracer
