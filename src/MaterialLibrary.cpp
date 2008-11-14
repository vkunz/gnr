#include "MaterialLibrary.h"
#include "Material.h"

#include <sstream>
#include <iostream>

using std::istringstream;
using std::stringstream;
using std::endl;

MaterialLibrary* MaterialLibrary::instance = 0;

MaterialLibrary::~MaterialLibrary()
{
}

MaterialLibrary::MaterialLibrary()
{
	istringstream defaults(
	    "newmtl amber\nKa0.0531 0.0531 0.0531\nKd 0.5755 0.2678 0.0000\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl amber_trans\nKa 0.0531 0.0531 0.0531\nKd 0.5755 0.2678 0.0000\nKs 0.3000 0.3000 0.3000\nillum 2\nd 0.8400\nNs 60.0000\n\
		\nnewmtl charcoal\nKa 0.0082 0.0082 0.0082\nKd 0.0041 0.0041 0.0041\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\n\
		\nnewmtl lavendar\nKa 0.1281 0.0857 0.2122\nKd 0.2187 0.0906 0.3469\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\n\
		\nnewmtl navy_blue\nKa 0.0000 0.0000 0.0490\nKd 0.0000 0.0000 0.0531\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl pale_green\nKa 0.0444 0.0898 0.0447\nKd 0.0712 0.3796 0.0490\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl pale_pink\nKa 0.0898 0.0444 0.0444\nKd 0.6531 0.2053 0.4160\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl pale_yellow\nKa 0.3606 0.3755 0.0935\nKd 0.6898 0.6211 0.1999\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl peach\nKa 0.3143 0.1187 0.0167\nKd 0.6367 0.1829 0.0156\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl periwinkle\nKa 0.0000 0.0000 0.1184\nKd 0.0000 0.0396 0.8286\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl redwood\nKa 0.0204 0.0027 0.0000\nKd 0.2571 0.0330 0.0000\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\n\
		\nnewmtl smoked_glass\nKa 0.0000 0.0000 0.0000\nKd 0.0041 0.0041 0.0041\nKs 0.1878 0.1878 0.1878\nillum 2\nd 0.9800\nNs 91.4700\n\
		\nnewmtl aqua_filter\nKa 0.0000 0.0000 0.0000\nKd 0.3743 0.6694 0.5791\nKs 0.1878 0.1878 0.1878\nillum 2\nd 0.9800\nNs 91.4700\n\
		\nnewmtl yellow_green\nKa 0.0000 0.0000 0.0000\nKd 0.1875 0.4082 0.0017\nKs 0.1878 0.1878 0.1878\nillum 2\nNs 91.4700\
		\nnewmtl bluetint\nKa 0.1100 0.4238 0.5388\nKd 0.0468 0.7115 0.9551\nKs 0.3184 0.3184 0.3184\nillum 9\nd 0.5700\nNs 60.0000\nsharpness 60.0000\n\
		\nnewmtl plasma\nKa 0.4082 0.0816 0.2129\nKd 1.0000 0.0776 0.4478\nKs 0.3000 0.3000 0.3000\nillum 9\nd 0.7500\nNs 60.0000\nsharpness 60.0000\n\
		\nnewmtl emerald\nKa 0.0470 1.0000 0.0000\nKd 0.0470 1.0000 0.0000\nKs 0.2000 0.2000 0.2000\nillum 9\nd 0.7500\nNs 60.0000\nsharpness 60.0000\n\
		\nnewmtl ruby\nKa 1.0000 0.0000 0.0000\nKd 1.0000 0.0000 0.0000\nKs 0.2000 0.2000 0.2000\nillum 9\nd 0.7500\nNs 60.0000\nsharpness 60.0000\n\
		\nnewmtl sapphire\nKa 0.0235 0.0000 1.0000\nKd 0.0235 0.0000 1.0000\nKs 0.2000 0.2000 0.2000\nillum 9\nd 0.7500\nNs 60.0000\nsharpness 60.0000\n\
		\nnewmtl white\nKa 0.4000 0.4000 0.4000\nKd 1.0000 1.0000 1.0000\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl red\nKa 0.4449 0.0000 0.0000\nKd 0.7714 0.0000 0.0000\nKs 0.8857 0.0000 0.0000\nillum 2\nNs 136.4300\
		\nnewmtl blue_pure\nKa 0.0000 0.0000 0.5000\nKd 0.0000 0.0000 1.0000\nKs 0.0000 0.0000 0.5000\nillum 2\nNs 65.8900\
		\nnewmtl lime\nKa 0.0000 0.5000 0.0000\nKd 0.0000 1.0000 0.0000\nKs 0.0000 0.5000 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl green\nKa 0.0000 0.2500 0.0000\nKd 0.0000 0.2500 0.0000\nKs 0.0000 0.2500 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl yellow\nKa 1.0000 0.6667 0.0000\nKd 1.0000 0.6667 0.0000\nKs 1.0000 0.6667 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl purple\nKa 0.5000 0.0000 1.0000\nKd 0.5000 0.0000 1.0000\nKs 0.5000 0.0000 1.0000\nillum 2\nNs 65.8900\
		\nnewmtl orange\nKa 1.0000 0.1667 0.0000\nKd 1.0000 0.1667 0.0000\nKs 1.0000 0.1667 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl grey\nKa 0.5000 0.5000 0.5000\nKd 0.1837 0.1837 0.1837\nKs 0.5000 0.5000 0.5000\nillum 2\nNs 65.8900\
		\nnewmtl rubber\nKa 0.0000 0.0000 0.0000\nKd 0.0100 0.0100 0.0100\nKs 0.1000 0.1000 0.1000\nillum 2\nNs 65.8900\
		\nnewmtl flaqua\nKa 0.0000 0.4000 0.4000\nKd 0.0000 0.5000 0.5000\nillum 1\
		\nnewmtl flblack\nKa 0.0000 0.0000 0.0000\nKd 0.0041 0.0041 0.0041\nillum 1\
		\nnewmtl flblue_pure\nKa 0.0000 0.0000 0.5592\nKd 0.0000 0.0000 0.7102\nillum 1\
		\nnewmtl flgrey\nKa 0.2163 0.2163 0.2163\nKd 0.5000 0.5000 0.5000\nillum 1\
		\nnewmtl fllime\nKa 0.0000 0.3673 0.0000\nKd 0.0000 1.0000 0.0000\nillum 1\
		\nnewmtl florange\nKa 0.6857 0.1143 0.0000\nKd 1.0000 0.1667 0.0000\nillum 1\
		\nnewmtl flpurple\nKa 0.2368 0.0000 0.4735\nKd 0.3755 0.0000 0.7510\nillum 1\
		\nnewmtl flred\nKa 0.4000 0.0000 0.0000\nKd 1.0000 0.0000 0.0000\nillum 1\
		\nnewmtl flyellow\nKa 0.7388 0.4925 0.0000\nKd 1.0000 0.6667 0.0000\nillum 1\
		\nnewmtl pink\nKa 0.9469 0.0078 0.2845\nKd 0.9878 0.1695 0.6702\nKs 0.7429 0.2972 0.2972\nillum 2\nNs 106.2000\
		\nnewmtl flbrown\nKa 0.0571 0.0066 0.0011\nKd 0.1102 0.0120 0.0013\nillum 1\
		\nnewmtl brown\nKa 0.1020 0.0185 0.0013\nKd 0.0857 0.0147 0.0000\nKs 0.1633 0.0240 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl glass\nKa 1.0000 1.0000 1.0000\nKd 0.4873 0.4919 0.5306\nKs 0.6406 0.6939 0.9020\nillum 2\nNs 200.0000\
		\nnewmtl flesh\nKa 0.4612 0.3638 0.2993\nKd 0.5265 0.4127 0.3374\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl aqua\nKa 0.0000 0.4000 0.4000\nKd 0.0000 0.5000 0.5000\nKs 0.5673 0.5673 0.5673\nillum 2\nNs 60.0000\
		\nnewmtl black\nKa 0.0000 0.0000 0.0000\nKd 0.0020 0.0020 0.0020\nKs 0.5184 0.5184 0.5184\nillum 2\nNs 157.3600\
		\nnewmtl silver\nKa 0.9551 0.9551 0.9551\nKd 0.6163 0.6163 0.6163\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl dkblue_pure\nKa 0.0000 0.0000 0.0449\nKd 0.0000 0.0000 0.1347\nKs 0.0000 0.0000 0.5673\nillum 2\nNs 65.8900\
		\nnewmtl fldkblue_pure\nKa 0.0000 0.0000 0.0449\nKd 0.0000 0.0000 0.1347\nillum 1\
		\nnewmtl dkgreen\nKa 0.0000 0.0122 0.0000\nKd 0.0058 0.0245 0.0000\nKs 0.0000 0.0490 0.0000\nillum 2\nNs 60.0000\
		\nnewmtl dkgrey\nKa 0.0490 0.0490 0.0490\nKd 0.0490 0.0490 0.0490\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl ltbrown\nKa 0.1306 0.0538 0.0250\nKd 0.2776 0.1143 0.0531\nKs 0.3000 0.1235 0.0574\nillum 2\nNs 60.0000\
		\nnewmtl fldkgreen\nKa 0.0000 0.0122 0.0000\nKd 0.0058 0.0245 0.0000\nillum 1\
		\nnewmtl flltbrown\nKa 0.1306 0.0538 0.0250\nKd 0.2776 0.1143 0.0531\nillum 1\
		\nnewmtl tan\nKa 0.4000 0.3121 0.1202\nKd 0.6612 0.5221 0.2186\nKs 0.5020 0.4118 0.2152\nillum 2\nNs 60.0000\
		\nnewmtl fltan\nKa 0.4000 0.3121 0.1202\nKd 0.6612 0.4567 0.1295\nillum 1\
		\nnewmtl brzskin\nKa 0.4408 0.2694 0.1592\nKd 0.3796 0.2898 0.2122\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 25.0000\
		\nnewmtl lips\nKa 0.4408 0.2694 0.1592\nKd 0.9265 0.2612 0.2898\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 25.0000\
		\nnewmtl redorange\nKa 0.3918 0.0576 0.0000\nKd 0.7551 0.0185 0.0000\nKs 0.4694 0.3224 0.1667\nillum 2\nNs 132.5600\
		\nnewmtl blutan\nKa 0.4408 0.2694 0.1592\nKd 0.0776 0.2571 0.2041\nKs 0.1467 0.1469 0.0965\nillum 2\nNs 25.0000\
		\nnewmtl bluteal\nKa 0.0041 0.1123 0.1224\nKd 0.0776 0.2571 0.2041\nKs 0.1467 0.1469 0.0965\nillum 2\nNs 25.0000\
		\nnewmtl pinktan\nKa 0.4408 0.2694 0.1592\nKd 0.6857 0.2571 0.2163\nKs 0.1467 0.1469 0.0965\nillum 2\nNs 25.0000\
		\nnewmtl brnhair\nKa 0.0612 0.0174 0.0066\nKd 0.0898 0.0302 0.0110\nKs 0.1306 0.0819 0.0352\nillum 2\nNs 60.4700\
		\nnewmtl blondhair\nKa 0.4449 0.2632 0.0509\nKd 0.5714 0.3283 0.0443\nKs 0.7755 0.4602 0.0918\nillum 2\nNs 4.6500\
		\nnewmtl flblonde\nKa 0.4449 0.2632 0.0509\nKd 0.5714 0.3283 0.0443\nillum 1\
		\nnewmtl yelloworng\nKa 0.5837 0.1715 0.0000\nKd 0.8857 0.2490 0.0000\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl bone\nKa 0.3061 0.1654 0.0650\nKd 0.9000 0.7626 0.4261\nKs 0.8939 0.7609 0.5509\nillum 2\nNs 200.0000\
		\nnewmtl teeth\nKa 0.6408 0.5554 0.3845\nKd 0.9837 0.7959 0.4694\nillum 1\
		\nnewmtl brass\nKa 0.2490 0.1102 0.0000\nKd 0.4776 0.1959 0.0000\nKs 0.5796 0.5796 0.5796\nillum 2\nNs 134.8800\
		\nnewmtl dkred\nKa 0.0939 0.0000 0.0000\nKd 0.2286 0.0000 0.0000\nKs 0.2490 0.0000 0.0000\nillum 2\nNs 60.0000\
		\nnewmtl taupe\nKa 0.1061 0.0709 0.0637\nKd 0.2041 0.1227 0.1058\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 84.5000\
		\nnewmtl dkteal\nKa 0.0000 0.0245 0.0163\nKd 0.0000 0.0653 0.0449\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 55.0400\
		\nnewmtl dkdkgrey\nKa 0.0000 0.0000 0.0000\nKd 0.0122 0.0122 0.0122\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl dkblue\nKa 0.0000 0.0029 0.0408\nKd 0.0000 0.0041 0.0571\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl gold\nKa 0.7224 0.1416 0.0000\nKd 1.0000 0.4898 0.0000\nKs 0.7184 0.3695 0.3695\nillum 2\nNs 123.2600\
		\nnewmtl redbrick\nKa 0.1102 0.0067 0.0067\nKd 0.3306 0.0398 0.0081\nillum 1\
		\nnewmtl flmustard\nKa 0.4245 0.2508 0.0000\nKd 0.8898 0.3531 0.0073\nillum 1\
		\nnewmtl flpinegreen\nKa 0.0367 0.0612 0.0204\nKd 0.1061 0.2163 0.0857\nillum 1\
		\nnewmtl fldkred\nKa 0.0939 0.0000 0.0000\nKd 0.2286 0.0082 0.0082\nillum 1\
		\nnewmtl fldkgreen2\nKa 0.0025 0.0122 0.0014\nKd 0.0245 0.0694 0.0041\nillum 1\
		\nnewmtl flmintgreen\nKa 0.0408 0.1429 0.0571\nKd 0.1306 0.2898 0.1673\nillum 1\
		\nnewmtl olivegreen\nKa 0.0167 0.0245 0.0000\nKd 0.0250 0.0367 0.0000\nKs 0.2257 0.2776 0.1167\nillum 2\nNs 97.6700\
		\nnewmtl skin\nKa 0.2286 0.0187 0.0187\nKd 0.1102 0.0328 0.0139\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 17.8300\
		\nnewmtl redbrown\nKa 0.1469 0.0031 0.0000\nKd 0.2816 0.0060 0.0000\nKs 0.3714 0.3714 0.3714\nillum 2\nNs 141.0900\
		\nnewmtl deepgreen\nKa 0.0000 0.0050 0.0000\nKd 0.0000 0.0204 0.0050\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 113.1800\
		\nnewmtl flltolivegreen\nKa 0.0167 0.0245 0.0000\nKd 0.0393 0.0531 0.0100\nillum 1\
		\nnewmtl jetflame\nKa 0.7714 0.0000 0.0000\nKd 0.9510 0.4939 0.0980\nKs 0.8531 0.5222 0.0000\nillum 2\nNs 132.5600\
		\nnewmtl brownskn\nKa 0.0122 0.0041 0.0000\nKd 0.0204 0.0082 0.0000\nKs 0.0735 0.0508 0.0321\nillum 2\nNs 20.1600\
		\nnewmtl greenskn\nKa 0.0816 0.0449 0.0000\nKd 0.0000 0.0735 0.0000\nKs 0.0490 0.1224 0.0898\nillum 3\nNs 46.5100\nsharpness 146.5100\
		\nnewmtl ltgrey\nKa 0.5000 0.5000 0.5000\nKd 0.3837 0.3837 0.3837\nKs 0.5000 0.5000 0.5000\nillum 2\nNs 65.8900\
		\nnewmtl bronze\nKa 0.0449 0.0204 0.0000\nKd 0.0653 0.0367 0.0122\nKs 0.0776 0.0408 0.0000\nillum 3\nNs 137.2100\nsharpness 125.5800\
		\nnewmtl bone1\nKa 0.6408 0.5554 0.3845\nKd 0.9837 0.7959 0.4694\nillum 1\
		\nnewmtl flwhite1\nKa 0.9306 0.9306 0.9306\nKd 1.0000 1.0000 1.0000\nillum 1\
		\nnewmtl flwhite\nKa 0.6449 0.6116 0.5447\nKd 0.9837 0.9309 0.8392\nKs 0.8082 0.7290 0.5708\nillum 2\nNs 200.0000\
		\nnewmtl shadow\nKd 0.0350 0.0248 0.0194\nillum 0\nd 0.7500\
		\nnewmtl fldkolivegreen\nKa 0.0056 0.0082 0.0000\nKd 0.0151 0.0204 0.0038\nillum 1\
		\nnewmtl fldkdkgrey\nKa 0.0000 0.0000 0.0000\nKd 0.0122 0.0122 0.0122\nillum 1\
		\nnewmtl lcdgreen\nKa 0.4000 0.4000 0.4000\nKd 0.5878 1.0000 0.5061\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl brownlips\nKa 0.1143 0.0694 0.0245\nKd 0.1429 0.0653 0.0408\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 25.0000\
		\nnewmtl muscle\nKa 0.2122 0.0077 0.0154\nKd 0.4204 0.0721 0.0856\nKs 0.1184 0.1184 0.1184\nillum 2\nNs 25.5800\
		\nnewmtl flltgrey\nKa 0.5224 0.5224 0.5224\nKd 0.8245 0.8245 0.8245\nillum 1\
		\nnewmtl offwhite.warm\nKa 0.5184 0.4501 0.3703\nKd 0.8367 0.6898 0.4490\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl offwhite.cool\nKa 0.5184 0.4501 0.3703\nKd 0.8367 0.6812 0.5703\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl yellowbrt\nKa 0.4000 0.4000 0.4000\nKd 1.0000 0.7837 0.0000\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl chappie\nKa 0.4000 0.4000 0.4000\nKd 0.5837 0.1796 0.0367\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 60.0000\
		\nnewmtl archwhite\nKa 0.2816 0.2816 0.2816\nKd 0.9959 0.9959 0.9959\nillum 1\
		\nnewmtl archwhite2\nKa 0.2816 0.2816 0.2816\nKd 0.8408 0.8408 0.8408\nillum 1\
		\nnewmtl lighttan\nKa 0.0980 0.0536 0.0220\nKd 0.7020 0.4210 0.2206\nKs 0.8286 0.8057 0.5851\nillum 2\nNs 177.5200\
		\nnewmtl lighttan2\nKa 0.0980 0.0492 0.0144\nKd 0.3143 0.1870 0.0962\nKs 0.8286 0.8057 0.5851\nillum 2\nNs 177.5200\
		\nnewmtl lighttan3\nKa 0.0980 0.0492 0.0144\nKd 0.1796 0.0829 0.0139\nKs 0.8286 0.8057 0.5851\nillum 2\nNs 177.5200\
		\nnewmtl lightyellow\nKa 0.5061 0.1983 0.0000\nKd 1.0000 0.9542 0.3388\nKs 1.0000 0.9060 0.0000\nillum 2\nNs 177.5200\
		\nnewmtl lighttannew\nKa 0.0980 0.0492 0.0144\nKd 0.7878 0.6070 0.3216\nKs 0.8286 0.8057 0.5851\nillum 2\nNs 177.5200\
		\nnewmtl default\nKa 0.4000 0.4000 0.4000\nKd 0.7102 0.7020 0.6531\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 128.0000\
		\nnewmtl ship2\nKa 0.0000 0.0000 0.0000\nKd 1.0000 1.0000 1.0000\nKs 0.1143 0.1143 0.1143\nillum 2\nNs 60.0000\
		\nnewmtl dkpurple\nKa 0.0082 0.0000 0.0163\nKd 0.0245 0.0000 0.0490\nKs 0.1266 0.0000 0.2531\nillum 2\nNs 65.8900\
		\nnewmtl dkorange\nKa 0.4041 0.0123 0.0000\nKd 0.7143 0.0350 0.0000\nKs 0.7102 0.0870 0.0000\nillum 2\nNs 65.8900\
		\nnewmtl mintgrn\nKa 0.0101 0.1959 0.0335\nKd 0.0245 0.4776 0.0816\nKs 0.0245 0.4776 0.0816\nillum 2\nNs 65.8900\
		\nnewmtl fgreen\nKa 0.0000 0.0449 0.0000\nKd 0.0000 0.0449 0.0004\nKs 0.0062 0.0694 0.0000\nillum 2\nNs 106.2000\
		\nnewmtl glassblutint\nKa 0.4000 0.4000 0.4000\nKd 0.5551 0.8000 0.7730\nKs 0.7969 0.9714 0.9223\nillum 4\nd 0.3300\nNs 60.0000\nsharpness 60.0000\
		\nnewmtl bflesh\nKa 0.0122 0.0122 0.0122\nKd 0.0245 0.0081 0.0021\nKs 0.0531 0.0460 0.0153\nillum 2\nNs 20.1600\
		\nnewmtl meh\nKa 0.4000 0.4000 0.4000\nKd 0.5551 0.8000 0.7730\nKs 0.7969 0.9714 0.9223\nillum 4\nd 0.7500\nNs 183.7200\nsharpness 60.0000\
		\nnewmtl violet\nKa 0.0083 0.0000 0.1265\nKd 0.0287 0.0269 0.1347\nKs 0.2267 0.4537 0.6612\nillum 2\nNs 96.9000\
		\nnewmtl iris\nKa 0.3061 0.0556 0.0037\nKd 0.0000 0.0572 0.3184\nKs 0.8041 0.6782 0.1477\nillum 2\nNs 188.3700\
		\nnewmtl blugrn\nKa 0.4408 0.4144 0.1592\nKd 0.0811 0.6408 0.2775\nKs 0.1467 0.1469 0.0965\nillum 2\nNs 25.0000\
		\nnewmtl glasstransparent\nKa 0.2163 0.2163 0.2163\nKd 0.4694 0.4694 0.4694\nKs 0.6082 0.6082 0.6082\nillum 4\nd 0.7500\nNs 200.0000\nsharpness 60.0000\
		\nnewmtl fleshtransparent\nKa 0.4000 0.2253 0.2253\nKd 0.6898 0.2942 0.1295\nKs 0.7388 0.4614 0.4614\nillum 4\nd 0.7500\nNs 6.2000\nsharpness 60.0000\
		\nnewmtl fldkgrey\nKa 0.0449 0.0449 0.0449\nKd 0.0939 0.0939 0.0939\nillum 1\
		\nnewmtl sky_blue\nKa 0.1363 0.2264 0.4122\nKd 0.1241 0.5931 0.8000\nKs 0.0490 0.0490 0.0490\nillum 2\nNs 13.9500\
		\nnewmtl fldkpurple\nKa 0.0443 0.0257 0.0776\nKd 0.1612 0.0000 0.3347\nKs 0.0000 0.0000 0.0000\nillum 2\nNs 13.9500\
		\nnewmtl dkbrown\nKa 0.0143 0.0062 0.0027\nKd 0.0087 0.0038 0.0016\nKs 0.2370 0.2147 0.1821\nillum 3\nNs 60.0000\nsharpness 60.0000\
		\nnewmtl bone2\nKa 0.6408 0.5388 0.3348\nKd 0.9837 0.8620 0.6504\nillum 1\
		\nnewmtl bluegrey\nKa 0.4000 0.4000 0.4000\nKd 0.1881 0.2786 0.2898\nKs 0.3000 0.3000 0.3000\nillum 2\nNs 14.7300\
		\nnewmtl metal\nKa 0.9102 0.8956 0.1932\nKd 0.9000 0.7626 0.4261\nKs 0.8939 0.8840 0.8683\nillum 2\nNs 200.0000\
		\nnewmtl sand_stone\nKa 0.1299 0.1177 0.0998\nKd 0.1256 0.1138 0.0965\nKs 0.2370 0.2147 0.1821\nillum 3\nNs 60.0000\nsharpness 60.0000\
		\nnewmtl hair\nKa 0.0013 0.0012 0.0010\nKd 0.0008 0.0007 0.0006\nKs 0.0000 0.0000 0.0000\nillum 3\nNs 60.0000\nsharpness 60.0000\n");
	import(defaults);
}

MaterialLibrary* MaterialLibrary::getInstance()
{
	if (!instance)
	{
		instance = new MaterialLibrary();
	}
	
	return instance;
}

void MaterialLibrary::destroy()
{
	delete instance;
	instance = 0;
}

MaterialLibrary::mat_citer MaterialLibrary::get(const string& name) const
{
	return m_lib.find(name);
}

void MaterialLibrary::insert(const string& name, const Material& mat)
{
	m_lib[name] = mat;
}

void MaterialLibrary::insert(Color color)
{
	Material mat;
	mat.Ambient() = color;
	mat.Diffuse() = color;
	mat.Alpha() = 1.0f;
	
	insert(color.getHex(), mat);
}

void MaterialLibrary::import(const string& fname)
{
	ifstream ifs(fname.c_str());
	import(ifs);
	ifs.close();
}

void MaterialLibrary::import(istream& is)
{
	m_is = &is;
	while (m_is->good())
	{
		m_material = new Material;
		if (getName())
		{
			while (getData() && m_is->good());
		}
		m_lib[m_matname] = *m_material;
		delete m_material;
		m_material = NULL;
	}
}

bool MaterialLibrary::getName()
{
	bool found = m_buf.substr(0, 7) == "newmtl ";
	while (m_is->good() && !found)
	{
		getline(*m_is, m_buf);
		found = m_buf.substr(0, 7) == "newmtl ";
	}
	
	if (found)
	{
		m_matname = m_buf.substr(7, string::npos);
	}
	
	return found;
}

bool MaterialLibrary::getData()
{
	bool gotData = true;
	m_buf.clear();
	if (m_is->good())
	{
		getline(*m_is, m_buf);
		gotData = m_buf.substr(0, 7) != "newmtl ";
	}
	
	if (gotData)
	{
		parseData();
	}
	
	return gotData;
}

void MaterialLibrary::parseData()
{
	if (m_buf.size() < 2)
		return;
		
	float r, g, b, a;
	r = g = b = a = 0.0f;
	
	stringstream ss(m_buf.substr(2, string::npos));
	
	switch (m_buf[0])
	{
	case 'K':
		ss >> r >> g >> b;
		switch (m_buf[1])
		{
		case 'a':
			m_material->Ambient().setAll(r, g, b);
			break;
		case 'd':
			m_material->Diffuse().setAll(r, g, b);
			break;
		case 's':
			m_material->Specular().setAll(r, g, b);
		default:
			break;
		}
	case 'd':
		ss >> m_material->Alpha();
		break;
	case 'N':
	{
		char c;
		ss >> c;
		ss >> c;
		ss >> m_material->Shininess();
	}
	break;
	default:
		break;
	}
}

MaterialLibrary::mat_citer MaterialLibrary::end() const
{
	return m_lib.end();
}

ostream& operator<< (ostream& out, const MaterialLibrary& m)
{
	for (MaterialLibrary::mat_citer it = m.m_lib.begin(); it != m.m_lib.end(); ++it)
	{
		out << "newmtl " << it->first << endl;
		out << it->second << endl;
	}
	return out;
}

