#include "vector.h"
#include "intersect.h"
#include "math.h"
#include "DxLib.h"

namespace t2k {

	// �_�Ƌ�`�̏Փ˔���
	bool isIntersectPointRect(const int point_x, const int point_y, const int rect_x, const int rect_y, const int rect_size) {
		int sx = rect_x - (rect_size >> 1);
		int sy = rect_y - (rect_size >> 1);
		int ex = sx + rect_size;
		int ey = sy + rect_size;
		if (point_x < sx) return false;
		if (point_x > ex) return false;
		if (point_y < sy) return false;
		if (point_y > ey) return false;
		return true;
	}

	// ��`�Ƌ�`
	bool isIntersectRectPrimitive(const int a_left, const int a_right, const int a_top, const int a_bottom,
		const int b_left, const int b_right, const int b_top, const int b_bottom) {
		if (a_right < b_left) return false;
		if (a_left > b_right) return false;
		if (a_top > b_bottom) return false;
		if (a_bottom < b_top) return false;
		return true;
	}

	// ��`�Ƌ�`
	bool isIntersectRect(const int a_rect_x, const int a_rect_y, const int a_rect_size_w, const int a_rect_size_h,
		const int b_rect_x, const int b_rect_y, const int b_rect_size_w, const int b_rect_size_h) {

		int a_right = a_rect_x + (a_rect_size_w >> 1);
		int a_left = a_rect_x - (a_rect_size_w >> 1);
		int a_top = a_rect_y - (a_rect_size_h >> 1);
		int a_bottom = a_rect_y + (a_rect_size_h >> 1);

		int b_right = b_rect_x + (b_rect_size_w >> 1);
		int b_left = b_rect_x - (b_rect_size_w >> 1);
		int b_top = b_rect_y - (b_rect_size_h >> 1);
		int b_bottom = b_rect_y + (b_rect_size_h >> 1);

		return isIntersectRectPrimitive(a_left, a_right, a_top, a_bottom, b_left, b_right, b_top, b_bottom);
	}

	// ��`�Ƌ�`�̏Փˌ��m & ���W�␳
	int isIntersectRectToCorrectPosition(t2k::Vector3& a_now, const t2k::Vector3 &a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h, const float correct_space) {

		const int NO_HIT = 0;
		const int CORRECT_LEFT = 1;
		const int CORRECT_RIGHT = 2;
		const int CORRECT_UP = 3;
		const int CORRECT_DOWN = 4;

		if (!t2k::isIntersectRect(a_now, a_rect_size_w, a_rect_size_h, b, b_rect_size_w, b_rect_size_h)) return NO_HIT;

		t2k::Vector3 a_near = t2k::getNearestRectPoint(a_prev, a_rect_size_w, a_rect_size_h, b);
		int n = t2k::getRegionPointAndRect(a_near, b, b_rect_size_w, b_rect_size_h);

		if (0 == n) {
			float y = (a_now - a_prev).y;
			// �������Ɉړ����Ă���ꍇ�͏�ɕ␳
			if (y >= 0) {
				a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space;
				return CORRECT_UP;
			}
			// ������Ɉړ����Ă���ꍇ�͍��E�ǂ��炩�ɕ␳
			else {
				// �E�ɕ␳
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space;
					return CORRECT_RIGHT;
				}
				// ���ɕ␳
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space;
					return CORRECT_LEFT;
				}
			}
		}
		else if (2 == n) {
			float y = (a_now - a_prev).y;
			// ������Ɉړ����Ă���ꍇ�͉��ɕ␳
			if (y <= 0) {
				a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space;
				return CORRECT_DOWN;
			}
			// ������Ɉړ����Ă���ꍇ�͍��E�ǂ��炩�ɕ␳
			else {
				// �E�ɕ␳
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space;
					return CORRECT_RIGHT;
				}
				// ���ɕ␳
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space;
					return CORRECT_LEFT;
				}
			}
		}
		else if (1 == n) {
			float x = (a_now - a_prev).x;
			// �������Ɉړ����Ă���ꍇ�͉E�ɕ␳
			if (x <= 0) {
				a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space;
				return CORRECT_RIGHT;
			}
			// �E�����Ɉړ����Ă���ꍇ�͏㉺�ǂ��炩�ɕ␳
			else {
				// ��ɕ␳
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space;
					return CORRECT_UP;
				}
				// ���ɕ␳
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space;
					return CORRECT_DOWN;
				}
			}
		}
		else if (3 == n) {
			float x = (a_now - a_prev).x;
			// �E�����Ɉړ����Ă���ꍇ�͍��ɕ␳
			if (x >= 0) {
				a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space;
				return CORRECT_RIGHT;
			}
			// �������Ɉړ����Ă���ꍇ�͏㉺�ǂ��炩�ɕ␳
			else {
				// ��ɕ␳
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space;
					return CORRECT_UP;
				}
				// ���ɕ␳
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space;
					return CORRECT_DOWN;
				}
			}
		}
		return NO_HIT;
	}


	// �~�Ɖ~
	bool isIntersectCircle(const t2k::Vector3& a, float a_radius, const t2k::Vector3& b, float b_radius) {
		float l = (a - b).length();
		return l < (a_radius + b_radius) ? true : false;
	}


}