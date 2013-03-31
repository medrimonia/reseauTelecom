#include <string>

namespace graphs{
	class Vertex{
	private:
		/**
		 * Each vertex has a name (3 digits until proof of contrary)
		 */
		std::string _name;
		int _x;
		int _y;
	public:
		Vertex();

		std::string getName();
		int getX();
		int getY();

		void setName(std::string newName);
		void setPosition(int x, int y);
	};
}
