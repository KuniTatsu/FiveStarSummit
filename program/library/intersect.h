#pragma once

namespace t2k {

	//-----------------------------------------------------------------------------------------------------
	// �_�Ƌ�`(�����`)�̂̏Փˌ��m
	// arg1...�_�̂����W
	// arg2...�_�̂����W
	// arg3...��`�̒��S�����W
	// arg4...��`�̒��S�����W
	// arg5...��`�̃T�C�Y
	// ret....[ �Փ˂��Ă��� : true ]   [ �Փ˂��Ă��Ȃ� : false ]
	bool isIntersectPointRect(const int point_x, const int point_y, const int rect_x, const int rect_y, const int rect_size);

	//-----------------------------------------------------------------------------------------------------
	// ��`�Ƌ�`�̏Փˌ��m ����`�̍���E�E���̒��_���W�w��
	// arg1...��`A�̍��̂����W
	// arg2...��`A�̉E�̂����W
	// arg3...��`A�̏�̂����W
	// arg4...��`A�̉��̂����W
	// arg5...��`B�̍��̂����W
	// arg6...��`B�̉E�̂����W
	// arg7...��`B�̏�̂����W
	// arg8...��`B�̉��̂����W
	// ret....[ �Փ˂��Ă��� : true ]   [ �Փ˂��Ă��Ȃ� : false ]
	bool isIntersectRectPrimitive(const int a_left, const int a_right, const int a_top, const int a_bottom,
		const int b_left, const int b_right, const int b_top, const int b_bottom);

	//-----------------------------------------------------------------------------------------------------
	// ��`�Ƌ�`�̏Փˌ��m�@����`�̒��S�ƕ������w��
	// arg1...��`A�̂����W
	// arg2...��`A�̂����W
	// arg3...��`A�̕�
	// arg4...��`A�̍���
	// arg5...��`B�̂����W
	// arg6...��`B�̂����W
	// arg7...��`B�̕�
	// arg8...��`B�̍���
	// ret....[ �Փ˂��Ă��� : true ]   [ �Փ˂��Ă��Ȃ� : false ]
	bool isIntersectRect(const int a_rect_x, const int a_rect_y, const int a_rect_size_w, const int a_rect_size_h,
		const int b_rect_x, const int b_rect_y, const int b_rect_size_w, const int b_rect_size_h);

	//-----------------------------------------------------------------------------------------------------
	// ��`�Ƌ�`�̏Փˌ��m�@����`�̒��S�ƕ������w��
	// arg1...��`A�̍��W
	// arg2...��`A�̕�
	// arg3...��`A�̍���
	// arg4...��`B�̍��W
	// arg5...��`B�̕�
	// arg6...��`B�̍���
	// ret....[ �Փ˂��Ă��� : true ]   [ �Փ˂��Ă��Ȃ� : false ]
	inline bool isIntersectRect(const t2k::Vector3& a, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h) {
		return isIntersectRect(a.x, a.y, a_rect_size_w, a_rect_size_h, b.x, b.y, b_rect_size_w, b_rect_size_h);
	}
 
	//-----------------------------------------------------------------------------------------------------
	// ��`�Ƌ�`�̏Փˌ��m & ���W�␳
	// arg1...��`A�̌��ݍ��W( �␳�Ώۂ̍��W�ϐ� )
	// arg2...��`A�̈ړ��O�̍��W
	// arg3...��`A�̕�
	// arg4...��`A�̍���
	// arg5...��`B�̍��W
	// arg6...��`B�̕�
	// arg7...��`B�̍���
	// arg8...�␳�̒ǉ��X�y�[�X( �ȗ��� �f�t�H���g 1.0f )
	// ret....[ �Փ˂��Ă��Ȃ� : 0 ] 
	//        [ �Ώۂ����ɕ␳ : 1 ] 
	//        [ �Ώۂ��E�ɕ␳ : 2 ]
	//        [ �Ώۂ���ɕ␳ : 3 ]
	//        [ �Ώۂ����ɕ␳ : 4 ]
	// tips...��`A���␳�Ώۂ̃I�u�W�F�N�g
	//        ��`B�͕Ǔ��̈ړ����Ȃ��I�u�W�F�N�g��z�肵�Ă��܂�
	int isIntersectRectToCorrectPosition( t2k::Vector3& a_now, const t2k::Vector3 &a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h, const float correct_space = 1.0f);


	//-----------------------------------------------------------------------------------------------------
	// �~�Ɖ~�̏Փˌ��m
	// arg1...�~A�̒��S���W
	// arg2...�~A�̔��a
	// arg3...�~B�̒��S���W
	// arg4...�~B�̔��a
	// ret....[ �Փ˂��Ă��� : true ]   [ �Փ˂��Ă��Ȃ� : false ]
	bool isIntersectCircle(const t2k::Vector3& a, float a_radius, const t2k::Vector3& b, float b_radius);



}
