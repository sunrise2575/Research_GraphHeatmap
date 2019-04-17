all:
	g++ -o tsv2heatmap main.cpp arg_kv_parser.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -std=c++11

clean:
	rm tsv2heatmap
