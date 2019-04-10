#include <utility>
using std::pair;

namespace game_framework
{
	class CMovingRect : public CRect
	{
	public:
		CMovingRect();
		CMovingRect(const CRect&, pair<int,int>, pair<int,int>);
		~CMovingRect();
		pair<int,int> getVel() const;
		void UpdatePos(CMovingRect&, float);
	private:
		friend bool RectOverlap(const CRect&, const CRect&);
		pair<int, int> FindDis(float) const;
		CRect DestRect(float) const;
		
		CRect bRect;
		pair<int, int> vel;
		pair<int, int> acc;
	};
}
