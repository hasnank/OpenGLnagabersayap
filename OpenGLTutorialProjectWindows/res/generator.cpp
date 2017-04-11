#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef pair<double,double> pii;
pii vertex;
vector<pii> vertexes;
int main(){
	freopen("plotgrafika.txt", "r", stdin);
	while(scanf("%lf%lf", &vertex.fi, &vertex.se) != EOF){

		vertex.fi -= 500;
		vertex.se -= 500;

		vertex.se *= -1;

		vertex.fi /= 500.0;
		vertex.se /= 500.0;

		vertexes.push_back(vertex);
	}
	fclose(stdin);

	freopen("generatedplot.txt", "w", stdout);
	printf("PLOT:\n");
	for(pii vert : vertexes){
		printf("%lff %lff\n", vert.fi, vert.se);
	}
	puts("");
	
	puts("VEC3 POSITION ONLY:");
	for(pii vert : vertexes){
		printf("Vertex(glm::vec3(%lff, %lff, 0)),\n", vert.fi, vert.se);
	}
	puts("");

	puts("VEC3 POSITION SAME COLOR:");
	for(pii vert : vertexes){
		printf("Vertex(glm::vec3(%lff, %lff, 0), glm::vec3(1.0f, 1.0f, 0.0f)),\n", vert.fi, vert.se);
	}
	puts("");	

	puts("VEC3 POSITION RANDOM COLOR:");
	for(pii vert : vertexes){
		double R = (rand() % 256) / 256.0;
		double G = (rand() % 256) / 256.0;
		double B = (rand() % 256) / 256.0;
		printf("Vertex(glm::vec3(%lff, %lff, 0), glm::vec3(%lff, %lff, %lff)),\n", vert.fi, vert.se, R, G, B);
	}
	puts("");	
	
	fclose(stdout);
	return 0;
}
