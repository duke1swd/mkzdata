if (buffer_selector == 0) {
	v = (C_0 * f1_c_0_3_v_0 +
		C_1 * (f1_c_0_3_v_1 + f1_c_0_3_v_3) +
		C_3 * (f1_c_0_3_v_2 + adc_b0.s_1.c_0)) >> 16;
	f2_c_0_0_v_1 = v;
	f2_c_0_3_v_3 = v;
	f2_c_0_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_2_v_0 +
		C_1 * (f2_c_0_2_v_1 + f2_c_0_2_v_3) +
		C_3 * (f2_c_0_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_0 +
		C_1 * (f1_c_0_0_v_1 + adc_b0.s_1.c_0) +
		C_3 * (f1_c_0_0_v_2 + adc_b0.s_3.c_0)) >> 16;
	f2_c_0_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_0 +
		C_1 * (adc_b0.s_1.c_0 + adc_b0.s_3.c_0) +
		C_3 * (f1_c_0_1_v_2 + adc_b0.s_5.c_0)) >> 16;
	f2_c_0_1_v_1 = v;
	f2_c_0_0_v_3 = v;
	f2_c_0_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_3_v_0 +
		C_1 * (f2_c_0_3_v_1 + f2_c_0_3_v_3) +
		C_3 * (f2_c_0_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_0 +
		C_1 * (adc_b0.s_3.c_0 + adc_b0.s_5.c_0) +
		C_3 * (adc_b0.s_1.c_0 + adc_b0.s_7.c_0)) >> 16;
	f2_c_0_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_0 +
		C_1 * (adc_b0.s_5.c_0 + adc_b0.s_7.c_0) +
		C_3 * (adc_b0.s_3.c_0 + adc_b0.s_9.c_0)) >> 16;
	f2_c_0_2_v_1 = v;
	f2_c_0_1_v_3 = v;
	f2_c_0_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_0_v_0 +
		C_1 * (f2_c_0_0_v_1 + f2_c_0_0_v_3) +
		C_3 * (f2_c_0_0_v_2 + v)) >> 16;
	f1_c_0_3_v_2 = adc_b0.s_11.c_0;
	v = (C_0 * adc_b0.s_8.c_0 +
		C_1 * (adc_b0.s_7.c_0 + adc_b0.s_9.c_0) +
		C_3 * (adc_b0.s_5.c_0 + adc_b0.s_11.c_0)) >> 16;
	f2_c_0_2_v_0 = v;
	f1_c_0_3_v_1 = adc_b0.s_13.c_0;
	f1_c_0_0_v_2 = adc_b0.s_13.c_0;
	v = (C_0 * adc_b0.s_10.c_0 +
		C_1 * (adc_b0.s_9.c_0 + adc_b0.s_11.c_0) +
		C_3 * (adc_b0.s_7.c_0 + adc_b0.s_13.c_0)) >> 16;
	f2_c_0_3_v_1 = v;
	f2_c_0_2_v_3 = v;
	f2_c_0_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_1_v_0 +
		C_1 * (f2_c_0_1_v_1 + f2_c_0_1_v_3) +
		C_3 * (f2_c_0_1_v_2 + v)) >> 16;
	f1_c_0_3_v_0 = adc_b0.s_14.c_0;
	f1_c_0_0_v_1 = adc_b0.s_15.c_0;
	f1_c_0_3_v_3 = adc_b0.s_15.c_0;
	f1_c_0_1_v_2 = adc_b0.s_15.c_0;
	v = (C_0 * adc_b0.s_12.c_0 +
		C_1 * (adc_b0.s_11.c_0 + adc_b0.s_13.c_0) +
		C_3 * (adc_b0.s_9.c_0 + adc_b0.s_15.c_0)) >> 16;
	f2_c_0_3_v_0 = v;
	v = (C_0 * f1_c_1_3_v_0 +
		C_1 * (f1_c_1_3_v_1 + f1_c_1_3_v_3) +
		C_3 * (f1_c_1_3_v_2 + adc_b0.s_1.c_1)) >> 16;
	f2_c_1_0_v_1 = v;
	f2_c_1_3_v_3 = v;
	f2_c_1_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_2_v_0 +
		C_1 * (f2_c_1_2_v_1 + f2_c_1_2_v_3) +
		C_3 * (f2_c_1_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_1 +
		C_1 * (f1_c_1_0_v_1 + adc_b0.s_1.c_1) +
		C_3 * (f1_c_1_0_v_2 + adc_b0.s_3.c_1)) >> 16;
	f2_c_1_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_1 +
		C_1 * (adc_b0.s_1.c_1 + adc_b0.s_3.c_1) +
		C_3 * (f1_c_1_1_v_2 + adc_b0.s_5.c_1)) >> 16;
	f2_c_1_1_v_1 = v;
	f2_c_1_0_v_3 = v;
	f2_c_1_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_3_v_0 +
		C_1 * (f2_c_1_3_v_1 + f2_c_1_3_v_3) +
		C_3 * (f2_c_1_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_1 +
		C_1 * (adc_b0.s_3.c_1 + adc_b0.s_5.c_1) +
		C_3 * (adc_b0.s_1.c_1 + adc_b0.s_7.c_1)) >> 16;
	f2_c_1_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_1 +
		C_1 * (adc_b0.s_5.c_1 + adc_b0.s_7.c_1) +
		C_3 * (adc_b0.s_3.c_1 + adc_b0.s_9.c_1)) >> 16;
	f2_c_1_2_v_1 = v;
	f2_c_1_1_v_3 = v;
	f2_c_1_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_0_v_0 +
		C_1 * (f2_c_1_0_v_1 + f2_c_1_0_v_3) +
		C_3 * (f2_c_1_0_v_2 + v)) >> 16;
	f1_c_1_3_v_2 = adc_b0.s_11.c_1;
	v = (C_0 * adc_b0.s_8.c_1 +
		C_1 * (adc_b0.s_7.c_1 + adc_b0.s_9.c_1) +
		C_3 * (adc_b0.s_5.c_1 + adc_b0.s_11.c_1)) >> 16;
	f2_c_1_2_v_0 = v;
	f1_c_1_3_v_1 = adc_b0.s_13.c_1;
	f1_c_1_0_v_2 = adc_b0.s_13.c_1;
	v = (C_0 * adc_b0.s_10.c_1 +
		C_1 * (adc_b0.s_9.c_1 + adc_b0.s_11.c_1) +
		C_3 * (adc_b0.s_7.c_1 + adc_b0.s_13.c_1)) >> 16;
	f2_c_1_3_v_1 = v;
	f2_c_1_2_v_3 = v;
	f2_c_1_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_1_v_0 +
		C_1 * (f2_c_1_1_v_1 + f2_c_1_1_v_3) +
		C_3 * (f2_c_1_1_v_2 + v)) >> 16;
	f1_c_1_3_v_0 = adc_b0.s_14.c_1;
	f1_c_1_0_v_1 = adc_b0.s_15.c_1;
	f1_c_1_3_v_3 = adc_b0.s_15.c_1;
	f1_c_1_1_v_2 = adc_b0.s_15.c_1;
	v = (C_0 * adc_b0.s_12.c_1 +
		C_1 * (adc_b0.s_11.c_1 + adc_b0.s_13.c_1) +
		C_3 * (adc_b0.s_9.c_1 + adc_b0.s_15.c_1)) >> 16;
	f2_c_1_3_v_0 = v;
	v = (C_0 * f1_c_2_3_v_0 +
		C_1 * (f1_c_2_3_v_1 + f1_c_2_3_v_3) +
		C_3 * (f1_c_2_3_v_2 + adc_b0.s_1.c_2)) >> 16;
	f2_c_2_0_v_1 = v;
	f2_c_2_3_v_3 = v;
	f2_c_2_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_2_v_0 +
		C_1 * (f2_c_2_2_v_1 + f2_c_2_2_v_3) +
		C_3 * (f2_c_2_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_2 +
		C_1 * (f1_c_2_0_v_1 + adc_b0.s_1.c_2) +
		C_3 * (f1_c_2_0_v_2 + adc_b0.s_3.c_2)) >> 16;
	f2_c_2_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_2 +
		C_1 * (adc_b0.s_1.c_2 + adc_b0.s_3.c_2) +
		C_3 * (f1_c_2_1_v_2 + adc_b0.s_5.c_2)) >> 16;
	f2_c_2_1_v_1 = v;
	f2_c_2_0_v_3 = v;
	f2_c_2_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_3_v_0 +
		C_1 * (f2_c_2_3_v_1 + f2_c_2_3_v_3) +
		C_3 * (f2_c_2_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_2 +
		C_1 * (adc_b0.s_3.c_2 + adc_b0.s_5.c_2) +
		C_3 * (adc_b0.s_1.c_2 + adc_b0.s_7.c_2)) >> 16;
	f2_c_2_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_2 +
		C_1 * (adc_b0.s_5.c_2 + adc_b0.s_7.c_2) +
		C_3 * (adc_b0.s_3.c_2 + adc_b0.s_9.c_2)) >> 16;
	f2_c_2_2_v_1 = v;
	f2_c_2_1_v_3 = v;
	f2_c_2_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_0_v_0 +
		C_1 * (f2_c_2_0_v_1 + f2_c_2_0_v_3) +
		C_3 * (f2_c_2_0_v_2 + v)) >> 16;
	f1_c_2_3_v_2 = adc_b0.s_11.c_2;
	v = (C_0 * adc_b0.s_8.c_2 +
		C_1 * (adc_b0.s_7.c_2 + adc_b0.s_9.c_2) +
		C_3 * (adc_b0.s_5.c_2 + adc_b0.s_11.c_2)) >> 16;
	f2_c_2_2_v_0 = v;
	f1_c_2_3_v_1 = adc_b0.s_13.c_2;
	f1_c_2_0_v_2 = adc_b0.s_13.c_2;
	v = (C_0 * adc_b0.s_10.c_2 +
		C_1 * (adc_b0.s_9.c_2 + adc_b0.s_11.c_2) +
		C_3 * (adc_b0.s_7.c_2 + adc_b0.s_13.c_2)) >> 16;
	f2_c_2_3_v_1 = v;
	f2_c_2_2_v_3 = v;
	f2_c_2_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_1_v_0 +
		C_1 * (f2_c_2_1_v_1 + f2_c_2_1_v_3) +
		C_3 * (f2_c_2_1_v_2 + v)) >> 16;
	f1_c_2_3_v_0 = adc_b0.s_14.c_2;
	f1_c_2_0_v_1 = adc_b0.s_15.c_2;
	f1_c_2_3_v_3 = adc_b0.s_15.c_2;
	f1_c_2_1_v_2 = adc_b0.s_15.c_2;
	v = (C_0 * adc_b0.s_12.c_2 +
		C_1 * (adc_b0.s_11.c_2 + adc_b0.s_13.c_2) +
		C_3 * (adc_b0.s_9.c_2 + adc_b0.s_15.c_2)) >> 16;
	f2_c_2_3_v_0 = v;
	v = (C_0 * f1_c_3_3_v_0 +
		C_1 * (f1_c_3_3_v_1 + f1_c_3_3_v_3) +
		C_3 * (f1_c_3_3_v_2 + adc_b0.s_1.c_3)) >> 16;
	f2_c_3_0_v_1 = v;
	f2_c_3_3_v_3 = v;
	f2_c_3_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_2_v_0 +
		C_1 * (f2_c_3_2_v_1 + f2_c_3_2_v_3) +
		C_3 * (f2_c_3_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_3 +
		C_1 * (f1_c_3_0_v_1 + adc_b0.s_1.c_3) +
		C_3 * (f1_c_3_0_v_2 + adc_b0.s_3.c_3)) >> 16;
	f2_c_3_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_3 +
		C_1 * (adc_b0.s_1.c_3 + adc_b0.s_3.c_3) +
		C_3 * (f1_c_3_1_v_2 + adc_b0.s_5.c_3)) >> 16;
	f2_c_3_1_v_1 = v;
	f2_c_3_0_v_3 = v;
	f2_c_3_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_3_v_0 +
		C_1 * (f2_c_3_3_v_1 + f2_c_3_3_v_3) +
		C_3 * (f2_c_3_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_3 +
		C_1 * (adc_b0.s_3.c_3 + adc_b0.s_5.c_3) +
		C_3 * (adc_b0.s_1.c_3 + adc_b0.s_7.c_3)) >> 16;
	f2_c_3_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_3 +
		C_1 * (adc_b0.s_5.c_3 + adc_b0.s_7.c_3) +
		C_3 * (adc_b0.s_3.c_3 + adc_b0.s_9.c_3)) >> 16;
	f2_c_3_2_v_1 = v;
	f2_c_3_1_v_3 = v;
	f2_c_3_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_0_v_0 +
		C_1 * (f2_c_3_0_v_1 + f2_c_3_0_v_3) +
		C_3 * (f2_c_3_0_v_2 + v)) >> 16;
	f1_c_3_3_v_2 = adc_b0.s_11.c_3;
	v = (C_0 * adc_b0.s_8.c_3 +
		C_1 * (adc_b0.s_7.c_3 + adc_b0.s_9.c_3) +
		C_3 * (adc_b0.s_5.c_3 + adc_b0.s_11.c_3)) >> 16;
	f2_c_3_2_v_0 = v;
	f1_c_3_3_v_1 = adc_b0.s_13.c_3;
	f1_c_3_0_v_2 = adc_b0.s_13.c_3;
	v = (C_0 * adc_b0.s_10.c_3 +
		C_1 * (adc_b0.s_9.c_3 + adc_b0.s_11.c_3) +
		C_3 * (adc_b0.s_7.c_3 + adc_b0.s_13.c_3)) >> 16;
	f2_c_3_3_v_1 = v;
	f2_c_3_2_v_3 = v;
	f2_c_3_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_1_v_0 +
		C_1 * (f2_c_3_1_v_1 + f2_c_3_1_v_3) +
		C_3 * (f2_c_3_1_v_2 + v)) >> 16;
	f1_c_3_3_v_0 = adc_b0.s_14.c_3;
	f1_c_3_0_v_1 = adc_b0.s_15.c_3;
	f1_c_3_3_v_3 = adc_b0.s_15.c_3;
	f1_c_3_1_v_2 = adc_b0.s_15.c_3;
	v = (C_0 * adc_b0.s_12.c_3 +
		C_1 * (adc_b0.s_11.c_3 + adc_b0.s_13.c_3) +
		C_3 * (adc_b0.s_9.c_3 + adc_b0.s_15.c_3)) >> 16;
	f2_c_3_3_v_0 = v;
	v = (C_0 * f1_c_4_3_v_0 +
		C_1 * (f1_c_4_3_v_1 + f1_c_4_3_v_3) +
		C_3 * (f1_c_4_3_v_2 + adc_b0.s_1.c_4)) >> 16;
	f2_c_4_0_v_1 = v;
	f2_c_4_3_v_3 = v;
	f2_c_4_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_2_v_0 +
		C_1 * (f2_c_4_2_v_1 + f2_c_4_2_v_3) +
		C_3 * (f2_c_4_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_4 +
		C_1 * (f1_c_4_0_v_1 + adc_b0.s_1.c_4) +
		C_3 * (f1_c_4_0_v_2 + adc_b0.s_3.c_4)) >> 16;
	f2_c_4_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_4 +
		C_1 * (adc_b0.s_1.c_4 + adc_b0.s_3.c_4) +
		C_3 * (f1_c_4_1_v_2 + adc_b0.s_5.c_4)) >> 16;
	f2_c_4_1_v_1 = v;
	f2_c_4_0_v_3 = v;
	f2_c_4_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_3_v_0 +
		C_1 * (f2_c_4_3_v_1 + f2_c_4_3_v_3) +
		C_3 * (f2_c_4_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_4 +
		C_1 * (adc_b0.s_3.c_4 + adc_b0.s_5.c_4) +
		C_3 * (adc_b0.s_1.c_4 + adc_b0.s_7.c_4)) >> 16;
	f2_c_4_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_4 +
		C_1 * (adc_b0.s_5.c_4 + adc_b0.s_7.c_4) +
		C_3 * (adc_b0.s_3.c_4 + adc_b0.s_9.c_4)) >> 16;
	f2_c_4_2_v_1 = v;
	f2_c_4_1_v_3 = v;
	f2_c_4_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_0_v_0 +
		C_1 * (f2_c_4_0_v_1 + f2_c_4_0_v_3) +
		C_3 * (f2_c_4_0_v_2 + v)) >> 16;
	f1_c_4_3_v_2 = adc_b0.s_11.c_4;
	v = (C_0 * adc_b0.s_8.c_4 +
		C_1 * (adc_b0.s_7.c_4 + adc_b0.s_9.c_4) +
		C_3 * (adc_b0.s_5.c_4 + adc_b0.s_11.c_4)) >> 16;
	f2_c_4_2_v_0 = v;
	f1_c_4_3_v_1 = adc_b0.s_13.c_4;
	f1_c_4_0_v_2 = adc_b0.s_13.c_4;
	v = (C_0 * adc_b0.s_10.c_4 +
		C_1 * (adc_b0.s_9.c_4 + adc_b0.s_11.c_4) +
		C_3 * (adc_b0.s_7.c_4 + adc_b0.s_13.c_4)) >> 16;
	f2_c_4_3_v_1 = v;
	f2_c_4_2_v_3 = v;
	f2_c_4_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_1_v_0 +
		C_1 * (f2_c_4_1_v_1 + f2_c_4_1_v_3) +
		C_3 * (f2_c_4_1_v_2 + v)) >> 16;
	f1_c_4_3_v_0 = adc_b0.s_14.c_4;
	f1_c_4_0_v_1 = adc_b0.s_15.c_4;
	f1_c_4_3_v_3 = adc_b0.s_15.c_4;
	f1_c_4_1_v_2 = adc_b0.s_15.c_4;
	v = (C_0 * adc_b0.s_12.c_4 +
		C_1 * (adc_b0.s_11.c_4 + adc_b0.s_13.c_4) +
		C_3 * (adc_b0.s_9.c_4 + adc_b0.s_15.c_4)) >> 16;
	f2_c_4_3_v_0 = v;
	v = (C_0 * f1_c_5_3_v_0 +
		C_1 * (f1_c_5_3_v_1 + f1_c_5_3_v_3) +
		C_3 * (f1_c_5_3_v_2 + adc_b0.s_1.c_5)) >> 16;
	f2_c_5_0_v_1 = v;
	f2_c_5_3_v_3 = v;
	f2_c_5_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_2_v_0 +
		C_1 * (f2_c_5_2_v_1 + f2_c_5_2_v_3) +
		C_3 * (f2_c_5_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_0.c_5 +
		C_1 * (f1_c_5_0_v_1 + adc_b0.s_1.c_5) +
		C_3 * (f1_c_5_0_v_2 + adc_b0.s_3.c_5)) >> 16;
	f2_c_5_0_v_0 = v;
	v = (C_0 * adc_b0.s_2.c_5 +
		C_1 * (adc_b0.s_1.c_5 + adc_b0.s_3.c_5) +
		C_3 * (f1_c_5_1_v_2 + adc_b0.s_5.c_5)) >> 16;
	f2_c_5_1_v_1 = v;
	f2_c_5_0_v_3 = v;
	f2_c_5_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_3_v_0 +
		C_1 * (f2_c_5_3_v_1 + f2_c_5_3_v_3) +
		C_3 * (f2_c_5_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b0.s_4.c_5 +
		C_1 * (adc_b0.s_3.c_5 + adc_b0.s_5.c_5) +
		C_3 * (adc_b0.s_1.c_5 + adc_b0.s_7.c_5)) >> 16;
	f2_c_5_1_v_0 = v;
	v = (C_0 * adc_b0.s_6.c_5 +
		C_1 * (adc_b0.s_5.c_5 + adc_b0.s_7.c_5) +
		C_3 * (adc_b0.s_3.c_5 + adc_b0.s_9.c_5)) >> 16;
	f2_c_5_2_v_1 = v;
	f2_c_5_1_v_3 = v;
	f2_c_5_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_0_v_0 +
		C_1 * (f2_c_5_0_v_1 + f2_c_5_0_v_3) +
		C_3 * (f2_c_5_0_v_2 + v)) >> 16;
	f1_c_5_3_v_2 = adc_b0.s_11.c_5;
	v = (C_0 * adc_b0.s_8.c_5 +
		C_1 * (adc_b0.s_7.c_5 + adc_b0.s_9.c_5) +
		C_3 * (adc_b0.s_5.c_5 + adc_b0.s_11.c_5)) >> 16;
	f2_c_5_2_v_0 = v;
	f1_c_5_3_v_1 = adc_b0.s_13.c_5;
	f1_c_5_0_v_2 = adc_b0.s_13.c_5;
	v = (C_0 * adc_b0.s_10.c_5 +
		C_1 * (adc_b0.s_9.c_5 + adc_b0.s_11.c_5) +
		C_3 * (adc_b0.s_7.c_5 + adc_b0.s_13.c_5)) >> 16;
	f2_c_5_3_v_1 = v;
	f2_c_5_2_v_3 = v;
	f2_c_5_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_1_v_0 +
		C_1 * (f2_c_5_1_v_1 + f2_c_5_1_v_3) +
		C_3 * (f2_c_5_1_v_2 + v)) >> 16;
	f1_c_5_3_v_0 = adc_b0.s_14.c_5;
	f1_c_5_0_v_1 = adc_b0.s_15.c_5;
	f1_c_5_3_v_3 = adc_b0.s_15.c_5;
	f1_c_5_1_v_2 = adc_b0.s_15.c_5;
	v = (C_0 * adc_b0.s_12.c_5 +
		C_1 * (adc_b0.s_11.c_5 + adc_b0.s_13.c_5) +
		C_3 * (adc_b0.s_9.c_5 + adc_b0.s_15.c_5)) >> 16;
	f2_c_5_3_v_0 = v;
} else if (buffer_selector == 1) {
	v = (C_0 * f1_c_0_3_v_0 +
		C_1 * (f1_c_0_3_v_1 + f1_c_0_3_v_3) +
		C_3 * (f1_c_0_3_v_2 + adc_b1.s_1.c_0)) >> 16;
	f2_c_0_0_v_1 = v;
	f2_c_0_3_v_3 = v;
	f2_c_0_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_2_v_0 +
		C_1 * (f2_c_0_2_v_1 + f2_c_0_2_v_3) +
		C_3 * (f2_c_0_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_0 +
		C_1 * (f1_c_0_0_v_1 + adc_b1.s_1.c_0) +
		C_3 * (f1_c_0_0_v_2 + adc_b1.s_3.c_0)) >> 16;
	f2_c_0_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_0 +
		C_1 * (adc_b1.s_1.c_0 + adc_b1.s_3.c_0) +
		C_3 * (f1_c_0_1_v_2 + adc_b1.s_5.c_0)) >> 16;
	f2_c_0_1_v_1 = v;
	f2_c_0_0_v_3 = v;
	f2_c_0_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_3_v_0 +
		C_1 * (f2_c_0_3_v_1 + f2_c_0_3_v_3) +
		C_3 * (f2_c_0_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_0 +
		C_1 * (adc_b1.s_3.c_0 + adc_b1.s_5.c_0) +
		C_3 * (adc_b1.s_1.c_0 + adc_b1.s_7.c_0)) >> 16;
	f2_c_0_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_0 +
		C_1 * (adc_b1.s_5.c_0 + adc_b1.s_7.c_0) +
		C_3 * (adc_b1.s_3.c_0 + adc_b1.s_9.c_0)) >> 16;
	f2_c_0_2_v_1 = v;
	f2_c_0_1_v_3 = v;
	f2_c_0_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_0_v_0 +
		C_1 * (f2_c_0_0_v_1 + f2_c_0_0_v_3) +
		C_3 * (f2_c_0_0_v_2 + v)) >> 16;
	f1_c_0_3_v_2 = adc_b1.s_11.c_0;
	v = (C_0 * adc_b1.s_8.c_0 +
		C_1 * (adc_b1.s_7.c_0 + adc_b1.s_9.c_0) +
		C_3 * (adc_b1.s_5.c_0 + adc_b1.s_11.c_0)) >> 16;
	f2_c_0_2_v_0 = v;
	f1_c_0_3_v_1 = adc_b1.s_13.c_0;
	f1_c_0_0_v_2 = adc_b1.s_13.c_0;
	v = (C_0 * adc_b1.s_10.c_0 +
		C_1 * (adc_b1.s_9.c_0 + adc_b1.s_11.c_0) +
		C_3 * (adc_b1.s_7.c_0 + adc_b1.s_13.c_0)) >> 16;
	f2_c_0_3_v_1 = v;
	f2_c_0_2_v_3 = v;
	f2_c_0_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_1_v_0 +
		C_1 * (f2_c_0_1_v_1 + f2_c_0_1_v_3) +
		C_3 * (f2_c_0_1_v_2 + v)) >> 16;
	f1_c_0_3_v_0 = adc_b1.s_14.c_0;
	f1_c_0_0_v_1 = adc_b1.s_15.c_0;
	f1_c_0_3_v_3 = adc_b1.s_15.c_0;
	f1_c_0_1_v_2 = adc_b1.s_15.c_0;
	v = (C_0 * adc_b1.s_12.c_0 +
		C_1 * (adc_b1.s_11.c_0 + adc_b1.s_13.c_0) +
		C_3 * (adc_b1.s_9.c_0 + adc_b1.s_15.c_0)) >> 16;
	f2_c_0_3_v_0 = v;
	v = (C_0 * f1_c_1_3_v_0 +
		C_1 * (f1_c_1_3_v_1 + f1_c_1_3_v_3) +
		C_3 * (f1_c_1_3_v_2 + adc_b1.s_1.c_1)) >> 16;
	f2_c_1_0_v_1 = v;
	f2_c_1_3_v_3 = v;
	f2_c_1_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_2_v_0 +
		C_1 * (f2_c_1_2_v_1 + f2_c_1_2_v_3) +
		C_3 * (f2_c_1_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_1 +
		C_1 * (f1_c_1_0_v_1 + adc_b1.s_1.c_1) +
		C_3 * (f1_c_1_0_v_2 + adc_b1.s_3.c_1)) >> 16;
	f2_c_1_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_1 +
		C_1 * (adc_b1.s_1.c_1 + adc_b1.s_3.c_1) +
		C_3 * (f1_c_1_1_v_2 + adc_b1.s_5.c_1)) >> 16;
	f2_c_1_1_v_1 = v;
	f2_c_1_0_v_3 = v;
	f2_c_1_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_3_v_0 +
		C_1 * (f2_c_1_3_v_1 + f2_c_1_3_v_3) +
		C_3 * (f2_c_1_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_1 +
		C_1 * (adc_b1.s_3.c_1 + adc_b1.s_5.c_1) +
		C_3 * (adc_b1.s_1.c_1 + adc_b1.s_7.c_1)) >> 16;
	f2_c_1_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_1 +
		C_1 * (adc_b1.s_5.c_1 + adc_b1.s_7.c_1) +
		C_3 * (adc_b1.s_3.c_1 + adc_b1.s_9.c_1)) >> 16;
	f2_c_1_2_v_1 = v;
	f2_c_1_1_v_3 = v;
	f2_c_1_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_0_v_0 +
		C_1 * (f2_c_1_0_v_1 + f2_c_1_0_v_3) +
		C_3 * (f2_c_1_0_v_2 + v)) >> 16;
	f1_c_1_3_v_2 = adc_b1.s_11.c_1;
	v = (C_0 * adc_b1.s_8.c_1 +
		C_1 * (adc_b1.s_7.c_1 + adc_b1.s_9.c_1) +
		C_3 * (adc_b1.s_5.c_1 + adc_b1.s_11.c_1)) >> 16;
	f2_c_1_2_v_0 = v;
	f1_c_1_3_v_1 = adc_b1.s_13.c_1;
	f1_c_1_0_v_2 = adc_b1.s_13.c_1;
	v = (C_0 * adc_b1.s_10.c_1 +
		C_1 * (adc_b1.s_9.c_1 + adc_b1.s_11.c_1) +
		C_3 * (adc_b1.s_7.c_1 + adc_b1.s_13.c_1)) >> 16;
	f2_c_1_3_v_1 = v;
	f2_c_1_2_v_3 = v;
	f2_c_1_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_1_v_0 +
		C_1 * (f2_c_1_1_v_1 + f2_c_1_1_v_3) +
		C_3 * (f2_c_1_1_v_2 + v)) >> 16;
	f1_c_1_3_v_0 = adc_b1.s_14.c_1;
	f1_c_1_0_v_1 = adc_b1.s_15.c_1;
	f1_c_1_3_v_3 = adc_b1.s_15.c_1;
	f1_c_1_1_v_2 = adc_b1.s_15.c_1;
	v = (C_0 * adc_b1.s_12.c_1 +
		C_1 * (adc_b1.s_11.c_1 + adc_b1.s_13.c_1) +
		C_3 * (adc_b1.s_9.c_1 + adc_b1.s_15.c_1)) >> 16;
	f2_c_1_3_v_0 = v;
	v = (C_0 * f1_c_2_3_v_0 +
		C_1 * (f1_c_2_3_v_1 + f1_c_2_3_v_3) +
		C_3 * (f1_c_2_3_v_2 + adc_b1.s_1.c_2)) >> 16;
	f2_c_2_0_v_1 = v;
	f2_c_2_3_v_3 = v;
	f2_c_2_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_2_v_0 +
		C_1 * (f2_c_2_2_v_1 + f2_c_2_2_v_3) +
		C_3 * (f2_c_2_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_2 +
		C_1 * (f1_c_2_0_v_1 + adc_b1.s_1.c_2) +
		C_3 * (f1_c_2_0_v_2 + adc_b1.s_3.c_2)) >> 16;
	f2_c_2_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_2 +
		C_1 * (adc_b1.s_1.c_2 + adc_b1.s_3.c_2) +
		C_3 * (f1_c_2_1_v_2 + adc_b1.s_5.c_2)) >> 16;
	f2_c_2_1_v_1 = v;
	f2_c_2_0_v_3 = v;
	f2_c_2_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_3_v_0 +
		C_1 * (f2_c_2_3_v_1 + f2_c_2_3_v_3) +
		C_3 * (f2_c_2_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_2 +
		C_1 * (adc_b1.s_3.c_2 + adc_b1.s_5.c_2) +
		C_3 * (adc_b1.s_1.c_2 + adc_b1.s_7.c_2)) >> 16;
	f2_c_2_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_2 +
		C_1 * (adc_b1.s_5.c_2 + adc_b1.s_7.c_2) +
		C_3 * (adc_b1.s_3.c_2 + adc_b1.s_9.c_2)) >> 16;
	f2_c_2_2_v_1 = v;
	f2_c_2_1_v_3 = v;
	f2_c_2_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_0_v_0 +
		C_1 * (f2_c_2_0_v_1 + f2_c_2_0_v_3) +
		C_3 * (f2_c_2_0_v_2 + v)) >> 16;
	f1_c_2_3_v_2 = adc_b1.s_11.c_2;
	v = (C_0 * adc_b1.s_8.c_2 +
		C_1 * (adc_b1.s_7.c_2 + adc_b1.s_9.c_2) +
		C_3 * (adc_b1.s_5.c_2 + adc_b1.s_11.c_2)) >> 16;
	f2_c_2_2_v_0 = v;
	f1_c_2_3_v_1 = adc_b1.s_13.c_2;
	f1_c_2_0_v_2 = adc_b1.s_13.c_2;
	v = (C_0 * adc_b1.s_10.c_2 +
		C_1 * (adc_b1.s_9.c_2 + adc_b1.s_11.c_2) +
		C_3 * (adc_b1.s_7.c_2 + adc_b1.s_13.c_2)) >> 16;
	f2_c_2_3_v_1 = v;
	f2_c_2_2_v_3 = v;
	f2_c_2_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_1_v_0 +
		C_1 * (f2_c_2_1_v_1 + f2_c_2_1_v_3) +
		C_3 * (f2_c_2_1_v_2 + v)) >> 16;
	f1_c_2_3_v_0 = adc_b1.s_14.c_2;
	f1_c_2_0_v_1 = adc_b1.s_15.c_2;
	f1_c_2_3_v_3 = adc_b1.s_15.c_2;
	f1_c_2_1_v_2 = adc_b1.s_15.c_2;
	v = (C_0 * adc_b1.s_12.c_2 +
		C_1 * (adc_b1.s_11.c_2 + adc_b1.s_13.c_2) +
		C_3 * (adc_b1.s_9.c_2 + adc_b1.s_15.c_2)) >> 16;
	f2_c_2_3_v_0 = v;
	v = (C_0 * f1_c_3_3_v_0 +
		C_1 * (f1_c_3_3_v_1 + f1_c_3_3_v_3) +
		C_3 * (f1_c_3_3_v_2 + adc_b1.s_1.c_3)) >> 16;
	f2_c_3_0_v_1 = v;
	f2_c_3_3_v_3 = v;
	f2_c_3_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_2_v_0 +
		C_1 * (f2_c_3_2_v_1 + f2_c_3_2_v_3) +
		C_3 * (f2_c_3_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_3 +
		C_1 * (f1_c_3_0_v_1 + adc_b1.s_1.c_3) +
		C_3 * (f1_c_3_0_v_2 + adc_b1.s_3.c_3)) >> 16;
	f2_c_3_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_3 +
		C_1 * (adc_b1.s_1.c_3 + adc_b1.s_3.c_3) +
		C_3 * (f1_c_3_1_v_2 + adc_b1.s_5.c_3)) >> 16;
	f2_c_3_1_v_1 = v;
	f2_c_3_0_v_3 = v;
	f2_c_3_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_3_v_0 +
		C_1 * (f2_c_3_3_v_1 + f2_c_3_3_v_3) +
		C_3 * (f2_c_3_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_3 +
		C_1 * (adc_b1.s_3.c_3 + adc_b1.s_5.c_3) +
		C_3 * (adc_b1.s_1.c_3 + adc_b1.s_7.c_3)) >> 16;
	f2_c_3_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_3 +
		C_1 * (adc_b1.s_5.c_3 + adc_b1.s_7.c_3) +
		C_3 * (adc_b1.s_3.c_3 + adc_b1.s_9.c_3)) >> 16;
	f2_c_3_2_v_1 = v;
	f2_c_3_1_v_3 = v;
	f2_c_3_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_0_v_0 +
		C_1 * (f2_c_3_0_v_1 + f2_c_3_0_v_3) +
		C_3 * (f2_c_3_0_v_2 + v)) >> 16;
	f1_c_3_3_v_2 = adc_b1.s_11.c_3;
	v = (C_0 * adc_b1.s_8.c_3 +
		C_1 * (adc_b1.s_7.c_3 + adc_b1.s_9.c_3) +
		C_3 * (adc_b1.s_5.c_3 + adc_b1.s_11.c_3)) >> 16;
	f2_c_3_2_v_0 = v;
	f1_c_3_3_v_1 = adc_b1.s_13.c_3;
	f1_c_3_0_v_2 = adc_b1.s_13.c_3;
	v = (C_0 * adc_b1.s_10.c_3 +
		C_1 * (adc_b1.s_9.c_3 + adc_b1.s_11.c_3) +
		C_3 * (adc_b1.s_7.c_3 + adc_b1.s_13.c_3)) >> 16;
	f2_c_3_3_v_1 = v;
	f2_c_3_2_v_3 = v;
	f2_c_3_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_1_v_0 +
		C_1 * (f2_c_3_1_v_1 + f2_c_3_1_v_3) +
		C_3 * (f2_c_3_1_v_2 + v)) >> 16;
	f1_c_3_3_v_0 = adc_b1.s_14.c_3;
	f1_c_3_0_v_1 = adc_b1.s_15.c_3;
	f1_c_3_3_v_3 = adc_b1.s_15.c_3;
	f1_c_3_1_v_2 = adc_b1.s_15.c_3;
	v = (C_0 * adc_b1.s_12.c_3 +
		C_1 * (adc_b1.s_11.c_3 + adc_b1.s_13.c_3) +
		C_3 * (adc_b1.s_9.c_3 + adc_b1.s_15.c_3)) >> 16;
	f2_c_3_3_v_0 = v;
	v = (C_0 * f1_c_4_3_v_0 +
		C_1 * (f1_c_4_3_v_1 + f1_c_4_3_v_3) +
		C_3 * (f1_c_4_3_v_2 + adc_b1.s_1.c_4)) >> 16;
	f2_c_4_0_v_1 = v;
	f2_c_4_3_v_3 = v;
	f2_c_4_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_2_v_0 +
		C_1 * (f2_c_4_2_v_1 + f2_c_4_2_v_3) +
		C_3 * (f2_c_4_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_4 +
		C_1 * (f1_c_4_0_v_1 + adc_b1.s_1.c_4) +
		C_3 * (f1_c_4_0_v_2 + adc_b1.s_3.c_4)) >> 16;
	f2_c_4_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_4 +
		C_1 * (adc_b1.s_1.c_4 + adc_b1.s_3.c_4) +
		C_3 * (f1_c_4_1_v_2 + adc_b1.s_5.c_4)) >> 16;
	f2_c_4_1_v_1 = v;
	f2_c_4_0_v_3 = v;
	f2_c_4_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_3_v_0 +
		C_1 * (f2_c_4_3_v_1 + f2_c_4_3_v_3) +
		C_3 * (f2_c_4_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_4 +
		C_1 * (adc_b1.s_3.c_4 + adc_b1.s_5.c_4) +
		C_3 * (adc_b1.s_1.c_4 + adc_b1.s_7.c_4)) >> 16;
	f2_c_4_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_4 +
		C_1 * (adc_b1.s_5.c_4 + adc_b1.s_7.c_4) +
		C_3 * (adc_b1.s_3.c_4 + adc_b1.s_9.c_4)) >> 16;
	f2_c_4_2_v_1 = v;
	f2_c_4_1_v_3 = v;
	f2_c_4_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_0_v_0 +
		C_1 * (f2_c_4_0_v_1 + f2_c_4_0_v_3) +
		C_3 * (f2_c_4_0_v_2 + v)) >> 16;
	f1_c_4_3_v_2 = adc_b1.s_11.c_4;
	v = (C_0 * adc_b1.s_8.c_4 +
		C_1 * (adc_b1.s_7.c_4 + adc_b1.s_9.c_4) +
		C_3 * (adc_b1.s_5.c_4 + adc_b1.s_11.c_4)) >> 16;
	f2_c_4_2_v_0 = v;
	f1_c_4_3_v_1 = adc_b1.s_13.c_4;
	f1_c_4_0_v_2 = adc_b1.s_13.c_4;
	v = (C_0 * adc_b1.s_10.c_4 +
		C_1 * (adc_b1.s_9.c_4 + adc_b1.s_11.c_4) +
		C_3 * (adc_b1.s_7.c_4 + adc_b1.s_13.c_4)) >> 16;
	f2_c_4_3_v_1 = v;
	f2_c_4_2_v_3 = v;
	f2_c_4_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_1_v_0 +
		C_1 * (f2_c_4_1_v_1 + f2_c_4_1_v_3) +
		C_3 * (f2_c_4_1_v_2 + v)) >> 16;
	f1_c_4_3_v_0 = adc_b1.s_14.c_4;
	f1_c_4_0_v_1 = adc_b1.s_15.c_4;
	f1_c_4_3_v_3 = adc_b1.s_15.c_4;
	f1_c_4_1_v_2 = adc_b1.s_15.c_4;
	v = (C_0 * adc_b1.s_12.c_4 +
		C_1 * (adc_b1.s_11.c_4 + adc_b1.s_13.c_4) +
		C_3 * (adc_b1.s_9.c_4 + adc_b1.s_15.c_4)) >> 16;
	f2_c_4_3_v_0 = v;
	v = (C_0 * f1_c_5_3_v_0 +
		C_1 * (f1_c_5_3_v_1 + f1_c_5_3_v_3) +
		C_3 * (f1_c_5_3_v_2 + adc_b1.s_1.c_5)) >> 16;
	f2_c_5_0_v_1 = v;
	f2_c_5_3_v_3 = v;
	f2_c_5_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_2_v_0 +
		C_1 * (f2_c_5_2_v_1 + f2_c_5_2_v_3) +
		C_3 * (f2_c_5_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_0.c_5 +
		C_1 * (f1_c_5_0_v_1 + adc_b1.s_1.c_5) +
		C_3 * (f1_c_5_0_v_2 + adc_b1.s_3.c_5)) >> 16;
	f2_c_5_0_v_0 = v;
	v = (C_0 * adc_b1.s_2.c_5 +
		C_1 * (adc_b1.s_1.c_5 + adc_b1.s_3.c_5) +
		C_3 * (f1_c_5_1_v_2 + adc_b1.s_5.c_5)) >> 16;
	f2_c_5_1_v_1 = v;
	f2_c_5_0_v_3 = v;
	f2_c_5_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_3_v_0 +
		C_1 * (f2_c_5_3_v_1 + f2_c_5_3_v_3) +
		C_3 * (f2_c_5_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b1.s_4.c_5 +
		C_1 * (adc_b1.s_3.c_5 + adc_b1.s_5.c_5) +
		C_3 * (adc_b1.s_1.c_5 + adc_b1.s_7.c_5)) >> 16;
	f2_c_5_1_v_0 = v;
	v = (C_0 * adc_b1.s_6.c_5 +
		C_1 * (adc_b1.s_5.c_5 + adc_b1.s_7.c_5) +
		C_3 * (adc_b1.s_3.c_5 + adc_b1.s_9.c_5)) >> 16;
	f2_c_5_2_v_1 = v;
	f2_c_5_1_v_3 = v;
	f2_c_5_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_0_v_0 +
		C_1 * (f2_c_5_0_v_1 + f2_c_5_0_v_3) +
		C_3 * (f2_c_5_0_v_2 + v)) >> 16;
	f1_c_5_3_v_2 = adc_b1.s_11.c_5;
	v = (C_0 * adc_b1.s_8.c_5 +
		C_1 * (adc_b1.s_7.c_5 + adc_b1.s_9.c_5) +
		C_3 * (adc_b1.s_5.c_5 + adc_b1.s_11.c_5)) >> 16;
	f2_c_5_2_v_0 = v;
	f1_c_5_3_v_1 = adc_b1.s_13.c_5;
	f1_c_5_0_v_2 = adc_b1.s_13.c_5;
	v = (C_0 * adc_b1.s_10.c_5 +
		C_1 * (adc_b1.s_9.c_5 + adc_b1.s_11.c_5) +
		C_3 * (adc_b1.s_7.c_5 + adc_b1.s_13.c_5)) >> 16;
	f2_c_5_3_v_1 = v;
	f2_c_5_2_v_3 = v;
	f2_c_5_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_1_v_0 +
		C_1 * (f2_c_5_1_v_1 + f2_c_5_1_v_3) +
		C_3 * (f2_c_5_1_v_2 + v)) >> 16;
	f1_c_5_3_v_0 = adc_b1.s_14.c_5;
	f1_c_5_0_v_1 = adc_b1.s_15.c_5;
	f1_c_5_3_v_3 = adc_b1.s_15.c_5;
	f1_c_5_1_v_2 = adc_b1.s_15.c_5;
	v = (C_0 * adc_b1.s_12.c_5 +
		C_1 * (adc_b1.s_11.c_5 + adc_b1.s_13.c_5) +
		C_3 * (adc_b1.s_9.c_5 + adc_b1.s_15.c_5)) >> 16;
	f2_c_5_3_v_0 = v;
} else if (buffer_selector == 2) {
	v = (C_0 * f1_c_0_3_v_0 +
		C_1 * (f1_c_0_3_v_1 + f1_c_0_3_v_3) +
		C_3 * (f1_c_0_3_v_2 + adc_b2.s_1.c_0)) >> 16;
	f2_c_0_0_v_1 = v;
	f2_c_0_3_v_3 = v;
	f2_c_0_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_2_v_0 +
		C_1 * (f2_c_0_2_v_1 + f2_c_0_2_v_3) +
		C_3 * (f2_c_0_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_0 +
		C_1 * (f1_c_0_0_v_1 + adc_b2.s_1.c_0) +
		C_3 * (f1_c_0_0_v_2 + adc_b2.s_3.c_0)) >> 16;
	f2_c_0_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_0 +
		C_1 * (adc_b2.s_1.c_0 + adc_b2.s_3.c_0) +
		C_3 * (f1_c_0_1_v_2 + adc_b2.s_5.c_0)) >> 16;
	f2_c_0_1_v_1 = v;
	f2_c_0_0_v_3 = v;
	f2_c_0_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_3_v_0 +
		C_1 * (f2_c_0_3_v_1 + f2_c_0_3_v_3) +
		C_3 * (f2_c_0_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_0 +
		C_1 * (adc_b2.s_3.c_0 + adc_b2.s_5.c_0) +
		C_3 * (adc_b2.s_1.c_0 + adc_b2.s_7.c_0)) >> 16;
	f2_c_0_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_0 +
		C_1 * (adc_b2.s_5.c_0 + adc_b2.s_7.c_0) +
		C_3 * (adc_b2.s_3.c_0 + adc_b2.s_9.c_0)) >> 16;
	f2_c_0_2_v_1 = v;
	f2_c_0_1_v_3 = v;
	f2_c_0_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_0_v_0 +
		C_1 * (f2_c_0_0_v_1 + f2_c_0_0_v_3) +
		C_3 * (f2_c_0_0_v_2 + v)) >> 16;
	f1_c_0_3_v_2 = adc_b2.s_11.c_0;
	v = (C_0 * adc_b2.s_8.c_0 +
		C_1 * (adc_b2.s_7.c_0 + adc_b2.s_9.c_0) +
		C_3 * (adc_b2.s_5.c_0 + adc_b2.s_11.c_0)) >> 16;
	f2_c_0_2_v_0 = v;
	f1_c_0_3_v_1 = adc_b2.s_13.c_0;
	f1_c_0_0_v_2 = adc_b2.s_13.c_0;
	v = (C_0 * adc_b2.s_10.c_0 +
		C_1 * (adc_b2.s_9.c_0 + adc_b2.s_11.c_0) +
		C_3 * (adc_b2.s_7.c_0 + adc_b2.s_13.c_0)) >> 16;
	f2_c_0_3_v_1 = v;
	f2_c_0_2_v_3 = v;
	f2_c_0_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_0_1_v_0 +
		C_1 * (f2_c_0_1_v_1 + f2_c_0_1_v_3) +
		C_3 * (f2_c_0_1_v_2 + v)) >> 16;
	f1_c_0_3_v_0 = adc_b2.s_14.c_0;
	f1_c_0_0_v_1 = adc_b2.s_15.c_0;
	f1_c_0_3_v_3 = adc_b2.s_15.c_0;
	f1_c_0_1_v_2 = adc_b2.s_15.c_0;
	v = (C_0 * adc_b2.s_12.c_0 +
		C_1 * (adc_b2.s_11.c_0 + adc_b2.s_13.c_0) +
		C_3 * (adc_b2.s_9.c_0 + adc_b2.s_15.c_0)) >> 16;
	f2_c_0_3_v_0 = v;
	v = (C_0 * f1_c_1_3_v_0 +
		C_1 * (f1_c_1_3_v_1 + f1_c_1_3_v_3) +
		C_3 * (f1_c_1_3_v_2 + adc_b2.s_1.c_1)) >> 16;
	f2_c_1_0_v_1 = v;
	f2_c_1_3_v_3 = v;
	f2_c_1_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_2_v_0 +
		C_1 * (f2_c_1_2_v_1 + f2_c_1_2_v_3) +
		C_3 * (f2_c_1_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_1 +
		C_1 * (f1_c_1_0_v_1 + adc_b2.s_1.c_1) +
		C_3 * (f1_c_1_0_v_2 + adc_b2.s_3.c_1)) >> 16;
	f2_c_1_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_1 +
		C_1 * (adc_b2.s_1.c_1 + adc_b2.s_3.c_1) +
		C_3 * (f1_c_1_1_v_2 + adc_b2.s_5.c_1)) >> 16;
	f2_c_1_1_v_1 = v;
	f2_c_1_0_v_3 = v;
	f2_c_1_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_3_v_0 +
		C_1 * (f2_c_1_3_v_1 + f2_c_1_3_v_3) +
		C_3 * (f2_c_1_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_1 +
		C_1 * (adc_b2.s_3.c_1 + adc_b2.s_5.c_1) +
		C_3 * (adc_b2.s_1.c_1 + adc_b2.s_7.c_1)) >> 16;
	f2_c_1_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_1 +
		C_1 * (adc_b2.s_5.c_1 + adc_b2.s_7.c_1) +
		C_3 * (adc_b2.s_3.c_1 + adc_b2.s_9.c_1)) >> 16;
	f2_c_1_2_v_1 = v;
	f2_c_1_1_v_3 = v;
	f2_c_1_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_0_v_0 +
		C_1 * (f2_c_1_0_v_1 + f2_c_1_0_v_3) +
		C_3 * (f2_c_1_0_v_2 + v)) >> 16;
	f1_c_1_3_v_2 = adc_b2.s_11.c_1;
	v = (C_0 * adc_b2.s_8.c_1 +
		C_1 * (adc_b2.s_7.c_1 + adc_b2.s_9.c_1) +
		C_3 * (adc_b2.s_5.c_1 + adc_b2.s_11.c_1)) >> 16;
	f2_c_1_2_v_0 = v;
	f1_c_1_3_v_1 = adc_b2.s_13.c_1;
	f1_c_1_0_v_2 = adc_b2.s_13.c_1;
	v = (C_0 * adc_b2.s_10.c_1 +
		C_1 * (adc_b2.s_9.c_1 + adc_b2.s_11.c_1) +
		C_3 * (adc_b2.s_7.c_1 + adc_b2.s_13.c_1)) >> 16;
	f2_c_1_3_v_1 = v;
	f2_c_1_2_v_3 = v;
	f2_c_1_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_1_1_v_0 +
		C_1 * (f2_c_1_1_v_1 + f2_c_1_1_v_3) +
		C_3 * (f2_c_1_1_v_2 + v)) >> 16;
	f1_c_1_3_v_0 = adc_b2.s_14.c_1;
	f1_c_1_0_v_1 = adc_b2.s_15.c_1;
	f1_c_1_3_v_3 = adc_b2.s_15.c_1;
	f1_c_1_1_v_2 = adc_b2.s_15.c_1;
	v = (C_0 * adc_b2.s_12.c_1 +
		C_1 * (adc_b2.s_11.c_1 + adc_b2.s_13.c_1) +
		C_3 * (adc_b2.s_9.c_1 + adc_b2.s_15.c_1)) >> 16;
	f2_c_1_3_v_0 = v;
	v = (C_0 * f1_c_2_3_v_0 +
		C_1 * (f1_c_2_3_v_1 + f1_c_2_3_v_3) +
		C_3 * (f1_c_2_3_v_2 + adc_b2.s_1.c_2)) >> 16;
	f2_c_2_0_v_1 = v;
	f2_c_2_3_v_3 = v;
	f2_c_2_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_2_v_0 +
		C_1 * (f2_c_2_2_v_1 + f2_c_2_2_v_3) +
		C_3 * (f2_c_2_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_2 +
		C_1 * (f1_c_2_0_v_1 + adc_b2.s_1.c_2) +
		C_3 * (f1_c_2_0_v_2 + adc_b2.s_3.c_2)) >> 16;
	f2_c_2_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_2 +
		C_1 * (adc_b2.s_1.c_2 + adc_b2.s_3.c_2) +
		C_3 * (f1_c_2_1_v_2 + adc_b2.s_5.c_2)) >> 16;
	f2_c_2_1_v_1 = v;
	f2_c_2_0_v_3 = v;
	f2_c_2_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_3_v_0 +
		C_1 * (f2_c_2_3_v_1 + f2_c_2_3_v_3) +
		C_3 * (f2_c_2_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_2 +
		C_1 * (adc_b2.s_3.c_2 + adc_b2.s_5.c_2) +
		C_3 * (adc_b2.s_1.c_2 + adc_b2.s_7.c_2)) >> 16;
	f2_c_2_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_2 +
		C_1 * (adc_b2.s_5.c_2 + adc_b2.s_7.c_2) +
		C_3 * (adc_b2.s_3.c_2 + adc_b2.s_9.c_2)) >> 16;
	f2_c_2_2_v_1 = v;
	f2_c_2_1_v_3 = v;
	f2_c_2_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_0_v_0 +
		C_1 * (f2_c_2_0_v_1 + f2_c_2_0_v_3) +
		C_3 * (f2_c_2_0_v_2 + v)) >> 16;
	f1_c_2_3_v_2 = adc_b2.s_11.c_2;
	v = (C_0 * adc_b2.s_8.c_2 +
		C_1 * (adc_b2.s_7.c_2 + adc_b2.s_9.c_2) +
		C_3 * (adc_b2.s_5.c_2 + adc_b2.s_11.c_2)) >> 16;
	f2_c_2_2_v_0 = v;
	f1_c_2_3_v_1 = adc_b2.s_13.c_2;
	f1_c_2_0_v_2 = adc_b2.s_13.c_2;
	v = (C_0 * adc_b2.s_10.c_2 +
		C_1 * (adc_b2.s_9.c_2 + adc_b2.s_11.c_2) +
		C_3 * (adc_b2.s_7.c_2 + adc_b2.s_13.c_2)) >> 16;
	f2_c_2_3_v_1 = v;
	f2_c_2_2_v_3 = v;
	f2_c_2_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_2_1_v_0 +
		C_1 * (f2_c_2_1_v_1 + f2_c_2_1_v_3) +
		C_3 * (f2_c_2_1_v_2 + v)) >> 16;
	f1_c_2_3_v_0 = adc_b2.s_14.c_2;
	f1_c_2_0_v_1 = adc_b2.s_15.c_2;
	f1_c_2_3_v_3 = adc_b2.s_15.c_2;
	f1_c_2_1_v_2 = adc_b2.s_15.c_2;
	v = (C_0 * adc_b2.s_12.c_2 +
		C_1 * (adc_b2.s_11.c_2 + adc_b2.s_13.c_2) +
		C_3 * (adc_b2.s_9.c_2 + adc_b2.s_15.c_2)) >> 16;
	f2_c_2_3_v_0 = v;
	v = (C_0 * f1_c_3_3_v_0 +
		C_1 * (f1_c_3_3_v_1 + f1_c_3_3_v_3) +
		C_3 * (f1_c_3_3_v_2 + adc_b2.s_1.c_3)) >> 16;
	f2_c_3_0_v_1 = v;
	f2_c_3_3_v_3 = v;
	f2_c_3_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_2_v_0 +
		C_1 * (f2_c_3_2_v_1 + f2_c_3_2_v_3) +
		C_3 * (f2_c_3_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_3 +
		C_1 * (f1_c_3_0_v_1 + adc_b2.s_1.c_3) +
		C_3 * (f1_c_3_0_v_2 + adc_b2.s_3.c_3)) >> 16;
	f2_c_3_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_3 +
		C_1 * (adc_b2.s_1.c_3 + adc_b2.s_3.c_3) +
		C_3 * (f1_c_3_1_v_2 + adc_b2.s_5.c_3)) >> 16;
	f2_c_3_1_v_1 = v;
	f2_c_3_0_v_3 = v;
	f2_c_3_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_3_v_0 +
		C_1 * (f2_c_3_3_v_1 + f2_c_3_3_v_3) +
		C_3 * (f2_c_3_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_3 +
		C_1 * (adc_b2.s_3.c_3 + adc_b2.s_5.c_3) +
		C_3 * (adc_b2.s_1.c_3 + adc_b2.s_7.c_3)) >> 16;
	f2_c_3_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_3 +
		C_1 * (adc_b2.s_5.c_3 + adc_b2.s_7.c_3) +
		C_3 * (adc_b2.s_3.c_3 + adc_b2.s_9.c_3)) >> 16;
	f2_c_3_2_v_1 = v;
	f2_c_3_1_v_3 = v;
	f2_c_3_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_0_v_0 +
		C_1 * (f2_c_3_0_v_1 + f2_c_3_0_v_3) +
		C_3 * (f2_c_3_0_v_2 + v)) >> 16;
	f1_c_3_3_v_2 = adc_b2.s_11.c_3;
	v = (C_0 * adc_b2.s_8.c_3 +
		C_1 * (adc_b2.s_7.c_3 + adc_b2.s_9.c_3) +
		C_3 * (adc_b2.s_5.c_3 + adc_b2.s_11.c_3)) >> 16;
	f2_c_3_2_v_0 = v;
	f1_c_3_3_v_1 = adc_b2.s_13.c_3;
	f1_c_3_0_v_2 = adc_b2.s_13.c_3;
	v = (C_0 * adc_b2.s_10.c_3 +
		C_1 * (adc_b2.s_9.c_3 + adc_b2.s_11.c_3) +
		C_3 * (adc_b2.s_7.c_3 + adc_b2.s_13.c_3)) >> 16;
	f2_c_3_3_v_1 = v;
	f2_c_3_2_v_3 = v;
	f2_c_3_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_3_1_v_0 +
		C_1 * (f2_c_3_1_v_1 + f2_c_3_1_v_3) +
		C_3 * (f2_c_3_1_v_2 + v)) >> 16;
	f1_c_3_3_v_0 = adc_b2.s_14.c_3;
	f1_c_3_0_v_1 = adc_b2.s_15.c_3;
	f1_c_3_3_v_3 = adc_b2.s_15.c_3;
	f1_c_3_1_v_2 = adc_b2.s_15.c_3;
	v = (C_0 * adc_b2.s_12.c_3 +
		C_1 * (adc_b2.s_11.c_3 + adc_b2.s_13.c_3) +
		C_3 * (adc_b2.s_9.c_3 + adc_b2.s_15.c_3)) >> 16;
	f2_c_3_3_v_0 = v;
	v = (C_0 * f1_c_4_3_v_0 +
		C_1 * (f1_c_4_3_v_1 + f1_c_4_3_v_3) +
		C_3 * (f1_c_4_3_v_2 + adc_b2.s_1.c_4)) >> 16;
	f2_c_4_0_v_1 = v;
	f2_c_4_3_v_3 = v;
	f2_c_4_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_2_v_0 +
		C_1 * (f2_c_4_2_v_1 + f2_c_4_2_v_3) +
		C_3 * (f2_c_4_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_4 +
		C_1 * (f1_c_4_0_v_1 + adc_b2.s_1.c_4) +
		C_3 * (f1_c_4_0_v_2 + adc_b2.s_3.c_4)) >> 16;
	f2_c_4_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_4 +
		C_1 * (adc_b2.s_1.c_4 + adc_b2.s_3.c_4) +
		C_3 * (f1_c_4_1_v_2 + adc_b2.s_5.c_4)) >> 16;
	f2_c_4_1_v_1 = v;
	f2_c_4_0_v_3 = v;
	f2_c_4_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_3_v_0 +
		C_1 * (f2_c_4_3_v_1 + f2_c_4_3_v_3) +
		C_3 * (f2_c_4_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_4 +
		C_1 * (adc_b2.s_3.c_4 + adc_b2.s_5.c_4) +
		C_3 * (adc_b2.s_1.c_4 + adc_b2.s_7.c_4)) >> 16;
	f2_c_4_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_4 +
		C_1 * (adc_b2.s_5.c_4 + adc_b2.s_7.c_4) +
		C_3 * (adc_b2.s_3.c_4 + adc_b2.s_9.c_4)) >> 16;
	f2_c_4_2_v_1 = v;
	f2_c_4_1_v_3 = v;
	f2_c_4_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_0_v_0 +
		C_1 * (f2_c_4_0_v_1 + f2_c_4_0_v_3) +
		C_3 * (f2_c_4_0_v_2 + v)) >> 16;
	f1_c_4_3_v_2 = adc_b2.s_11.c_4;
	v = (C_0 * adc_b2.s_8.c_4 +
		C_1 * (adc_b2.s_7.c_4 + adc_b2.s_9.c_4) +
		C_3 * (adc_b2.s_5.c_4 + adc_b2.s_11.c_4)) >> 16;
	f2_c_4_2_v_0 = v;
	f1_c_4_3_v_1 = adc_b2.s_13.c_4;
	f1_c_4_0_v_2 = adc_b2.s_13.c_4;
	v = (C_0 * adc_b2.s_10.c_4 +
		C_1 * (adc_b2.s_9.c_4 + adc_b2.s_11.c_4) +
		C_3 * (adc_b2.s_7.c_4 + adc_b2.s_13.c_4)) >> 16;
	f2_c_4_3_v_1 = v;
	f2_c_4_2_v_3 = v;
	f2_c_4_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_4_1_v_0 +
		C_1 * (f2_c_4_1_v_1 + f2_c_4_1_v_3) +
		C_3 * (f2_c_4_1_v_2 + v)) >> 16;
	f1_c_4_3_v_0 = adc_b2.s_14.c_4;
	f1_c_4_0_v_1 = adc_b2.s_15.c_4;
	f1_c_4_3_v_3 = adc_b2.s_15.c_4;
	f1_c_4_1_v_2 = adc_b2.s_15.c_4;
	v = (C_0 * adc_b2.s_12.c_4 +
		C_1 * (adc_b2.s_11.c_4 + adc_b2.s_13.c_4) +
		C_3 * (adc_b2.s_9.c_4 + adc_b2.s_15.c_4)) >> 16;
	f2_c_4_3_v_0 = v;
	v = (C_0 * f1_c_5_3_v_0 +
		C_1 * (f1_c_5_3_v_1 + f1_c_5_3_v_3) +
		C_3 * (f1_c_5_3_v_2 + adc_b2.s_1.c_5)) >> 16;
	f2_c_5_0_v_1 = v;
	f2_c_5_3_v_3 = v;
	f2_c_5_1_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_2_v_0 +
		C_1 * (f2_c_5_2_v_1 + f2_c_5_2_v_3) +
		C_3 * (f2_c_5_2_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_0.c_5 +
		C_1 * (f1_c_5_0_v_1 + adc_b2.s_1.c_5) +
		C_3 * (f1_c_5_0_v_2 + adc_b2.s_3.c_5)) >> 16;
	f2_c_5_0_v_0 = v;
	v = (C_0 * adc_b2.s_2.c_5 +
		C_1 * (adc_b2.s_1.c_5 + adc_b2.s_3.c_5) +
		C_3 * (f1_c_5_1_v_2 + adc_b2.s_5.c_5)) >> 16;
	f2_c_5_1_v_1 = v;
	f2_c_5_0_v_3 = v;
	f2_c_5_2_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_3_v_0 +
		C_1 * (f2_c_5_3_v_1 + f2_c_5_3_v_3) +
		C_3 * (f2_c_5_3_v_2 + v)) >> 16;
	v = (C_0 * adc_b2.s_4.c_5 +
		C_1 * (adc_b2.s_3.c_5 + adc_b2.s_5.c_5) +
		C_3 * (adc_b2.s_1.c_5 + adc_b2.s_7.c_5)) >> 16;
	f2_c_5_1_v_0 = v;
	v = (C_0 * adc_b2.s_6.c_5 +
		C_1 * (adc_b2.s_5.c_5 + adc_b2.s_7.c_5) +
		C_3 * (adc_b2.s_3.c_5 + adc_b2.s_9.c_5)) >> 16;
	f2_c_5_2_v_1 = v;
	f2_c_5_1_v_3 = v;
	f2_c_5_3_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_0_v_0 +
		C_1 * (f2_c_5_0_v_1 + f2_c_5_0_v_3) +
		C_3 * (f2_c_5_0_v_2 + v)) >> 16;
	f1_c_5_3_v_2 = adc_b2.s_11.c_5;
	v = (C_0 * adc_b2.s_8.c_5 +
		C_1 * (adc_b2.s_7.c_5 + adc_b2.s_9.c_5) +
		C_3 * (adc_b2.s_5.c_5 + adc_b2.s_11.c_5)) >> 16;
	f2_c_5_2_v_0 = v;
	f1_c_5_3_v_1 = adc_b2.s_13.c_5;
	f1_c_5_0_v_2 = adc_b2.s_13.c_5;
	v = (C_0 * adc_b2.s_10.c_5 +
		C_1 * (adc_b2.s_9.c_5 + adc_b2.s_11.c_5) +
		C_3 * (adc_b2.s_7.c_5 + adc_b2.s_13.c_5)) >> 16;
	f2_c_5_3_v_1 = v;
	f2_c_5_2_v_3 = v;
	f2_c_5_0_v_2 = v;
	*output_pointer++ = (C_0 * f2_c_5_1_v_0 +
		C_1 * (f2_c_5_1_v_1 + f2_c_5_1_v_3) +
		C_3 * (f2_c_5_1_v_2 + v)) >> 16;
	f1_c_5_3_v_0 = adc_b2.s_14.c_5;
	f1_c_5_0_v_1 = adc_b2.s_15.c_5;
	f1_c_5_3_v_3 = adc_b2.s_15.c_5;
	f1_c_5_1_v_2 = adc_b2.s_15.c_5;
	v = (C_0 * adc_b2.s_12.c_5 +
		C_1 * (adc_b2.s_11.c_5 + adc_b2.s_13.c_5) +
		C_3 * (adc_b2.s_9.c_5 + adc_b2.s_15.c_5)) >> 16;
	f2_c_5_3_v_0 = v;
}
