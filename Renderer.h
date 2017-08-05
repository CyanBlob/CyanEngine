class Renderer {
public:
	static void render();
	static void reshape(int, int);
	static void setZoom(int);
	static int getZoom();
private:
	static int zoom;
	Renderer();
	~Renderer();
};
