#ifndef LRDIRECTION_H
#define LRDIRECTION_H

namespace game_framework {
	/****************** LRDirection Class Declaration *****************/
	class LRDirection
	{
	public:
		LRDirection();
		void SetFlag(char);
		void ResetFlag(char);
		bool getDirection() const;
	private:
		bool flag;
		char key;
	};
}
#endif
