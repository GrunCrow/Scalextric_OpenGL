#include "car.h"
#include "car_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

car::car()
{
	CGMaterial* mtl0 = new CGMaterial();
	mtl0->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl0->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl0->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl0->SetShininess(2.0f);
	mtl0->InitTexture("tr0_main.tga");

	CGMaterial* mtl1 = new CGMaterial();
	mtl1->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl1->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl1->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl1->SetShininess(2.0f);
	mtl1->InitTexture("generic_main.tga");

	CGMaterial* mtl2 = new CGMaterial();
	mtl2->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl2->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl2->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl2->SetShininess(2.0f);
	mtl2->InitTexture("tr0_wheel.tga");

	CGMaterial* mtl3 = new CGMaterial();
	mtl3->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl3->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl3->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl3->SetShininess(2.0f);
	mtl3->InitTexture("light_glow.tga");

	CGMaterial* mtl4 = new CGMaterial();
	mtl4->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl4->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl4->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl4->SetShininess(2.0f);
	mtl4->InitTexture("tyre.tga");

	CGMaterial* mtl5 = new CGMaterial();
	mtl5->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl5->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl5->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl5->SetShininess(2.0f);
	mtl5->InitTexture("tread_slick.tga");

	CGMaterial* mtl6 = new CGMaterial();
	mtl6->SetAmbientReflect(0.0f, 0.0f, 0.0f);
	mtl6->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl6->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl6->SetShininess(2.0f);
	mtl6->InitTexture("glass.tga");

	pieces[0] = new car_0(mtl0);
	pieces[1] = new car_1(mtl1);
	pieces[2] = new car_2(mtl1);
	pieces[3] = new car_3(mtl1);
	pieces[4] = new car_4(mtl1);
	pieces[5] = new car_5(mtl1);
	pieces[6] = new car_6(mtl1);
	pieces[7] = new car_7(mtl1);
	pieces[8] = new car_8(mtl1);
	pieces[9] = new car_9(mtl1);
	pieces[10] = new car_10(mtl1);
	pieces[11] = new car_11(mtl1);
	pieces[12] = new car_12(mtl1);
	pieces[13] = new car_13(mtl1);
	pieces[14] = new car_14(mtl1);
	pieces[15] = new car_15(mtl0);
	pieces[16] = new car_16(mtl0);
	pieces[17] = new car_17(mtl0);
	pieces[18] = new car_18(mtl2);
	pieces[19] = new car_19(mtl2);
	pieces[20] = new car_20(mtl2);
	pieces[21] = new car_21(mtl2);
	pieces[22] = new car_22(mtl0);
	pieces[23] = new car_23(mtl0);
	pieces[24] = new car_24(mtl0);
	pieces[25] = new car_25(mtl3);
	pieces[26] = new car_26(mtl1);
	pieces[27] = new car_27(mtl1);
	pieces[28] = new car_28(mtl1);
	pieces[29] = new car_29(mtl1);
	pieces[30] = new car_30(mtl0);
	pieces[31] = new car_31(mtl0);
	pieces[32] = new car_32(mtl0);
	pieces[33] = new car_33(mtl0);
	pieces[34] = new car_34(mtl0);
	pieces[35] = new car_35(mtl0);
	pieces[36] = new car_36(mtl1);
	pieces[37] = new car_37(mtl1);
	pieces[38] = new car_38(mtl1);
	pieces[39] = new car_39(mtl1);
	pieces[40] = new car_40(mtl0);
	pieces[41] = new car_41(mtl1);
	pieces[42] = new car_42(mtl1);
	pieces[43] = new car_43(mtl1);
	pieces[44] = new car_44(mtl1);
	pieces[45] = new car_45(mtl4);
	pieces[46] = new car_46(mtl5);
	pieces[47] = new car_47(mtl4);
	pieces[48] = new car_48(mtl5);
	pieces[49] = new car_49(mtl4);
	pieces[50] = new car_50(mtl5);
	pieces[51] = new car_51(mtl4);
	pieces[52] = new car_52(mtl5);
	pieces[53] = new car_53(mtl0);
	pieces[54] = new car_54(mtl0);
	pieces[55] = new car_55(mtl0);
	pieces[56] = new car_56(mtl0);
	pieces[57] = new car_57(mtl1);
	pieces[58] = new car_58(mtl0);
	pieces[59] = new car_59(mtl0);
	pieces[60] = new car_60(mtl0);
	pieces[61] = new car_61(mtl0);
	pieces[62] = new car_62(mtl0);
	pieces[63] = new car_63(mtl0);
	pieces[64] = new car_64(mtl6);
	pieces[65] = new car_65(mtl0);
	pieces[66] = new car_66(mtl0);
	pieces[67] = new car_67(mtl0);
	pieces[68] = new car_68(mtl1);
}

car::~car()
{
	for (int i = 0; i < 69; i++) delete pieces[i];
}

int car::GetNumPieces()
{
	return 69;
}

CGPiece* car::GetPiece(int index)
{
	return pieces[index];
}

