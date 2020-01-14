
if (bf_desc == BFD_0) {
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c0 + adc_b2.s1.c0)) +
	C1 * ((uint32_t)(adc_b2.s15.c0 + adc_b2.s2.c0)) +
	C2 * ((uint32_t)(adc_b2.s14.c0 + adc_b2.s3.c0)) +
	C3 * ((uint32_t)(adc_b2.s13.c0 + adc_b2.s4.c0)) +
	C4 * ((uint32_t)(adc_b2.s12.c0 + adc_b2.s5.c0)) +
	C5 * ((uint32_t)(adc_b2.s11.c0 + adc_b2.s6.c0)) +
	C6 * ((uint32_t)(adc_b2.s10.c0 + adc_b2.s7.c0)) +
	C7 * ((uint32_t)(adc_b2.s9.c0 + adc_b2.s8.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c1 + adc_b2.s1.c1)) +
	C1 * ((uint32_t)(adc_b2.s15.c1 + adc_b2.s2.c1)) +
	C2 * ((uint32_t)(adc_b2.s14.c1 + adc_b2.s3.c1)) +
	C3 * ((uint32_t)(adc_b2.s13.c1 + adc_b2.s4.c1)) +
	C4 * ((uint32_t)(adc_b2.s12.c1 + adc_b2.s5.c1)) +
	C5 * ((uint32_t)(adc_b2.s11.c1 + adc_b2.s6.c1)) +
	C6 * ((uint32_t)(adc_b2.s10.c1 + adc_b2.s7.c1)) +
	C7 * ((uint32_t)(adc_b2.s9.c1 + adc_b2.s8.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c2 + adc_b2.s1.c2)) +
	C1 * ((uint32_t)(adc_b2.s15.c2 + adc_b2.s2.c2)) +
	C2 * ((uint32_t)(adc_b2.s14.c2 + adc_b2.s3.c2)) +
	C3 * ((uint32_t)(adc_b2.s13.c2 + adc_b2.s4.c2)) +
	C4 * ((uint32_t)(adc_b2.s12.c2 + adc_b2.s5.c2)) +
	C5 * ((uint32_t)(adc_b2.s11.c2 + adc_b2.s6.c2)) +
	C6 * ((uint32_t)(adc_b2.s10.c2 + adc_b2.s7.c2)) +
	C7 * ((uint32_t)(adc_b2.s9.c2 + adc_b2.s8.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c3 + adc_b2.s1.c3)) +
	C1 * ((uint32_t)(adc_b2.s15.c3 + adc_b2.s2.c3)) +
	C2 * ((uint32_t)(adc_b2.s14.c3 + adc_b2.s3.c3)) +
	C3 * ((uint32_t)(adc_b2.s13.c3 + adc_b2.s4.c3)) +
	C4 * ((uint32_t)(adc_b2.s12.c3 + adc_b2.s5.c3)) +
	C5 * ((uint32_t)(adc_b2.s11.c3 + adc_b2.s6.c3)) +
	C6 * ((uint32_t)(adc_b2.s10.c3 + adc_b2.s7.c3)) +
	C7 * ((uint32_t)(adc_b2.s9.c3 + adc_b2.s8.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c4 + adc_b2.s1.c4)) +
	C1 * ((uint32_t)(adc_b2.s15.c4 + adc_b2.s2.c4)) +
	C2 * ((uint32_t)(adc_b2.s14.c4 + adc_b2.s3.c4)) +
	C3 * ((uint32_t)(adc_b2.s13.c4 + adc_b2.s4.c4)) +
	C4 * ((uint32_t)(adc_b2.s12.c4 + adc_b2.s5.c4)) +
	C5 * ((uint32_t)(adc_b2.s11.c4 + adc_b2.s6.c4)) +
	C6 * ((uint32_t)(adc_b2.s10.c4 + adc_b2.s7.c4)) +
	C7 * ((uint32_t)(adc_b2.s9.c4 + adc_b2.s8.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s0.c5 + adc_b2.s1.c5)) +
	C1 * ((uint32_t)(adc_b2.s15.c5 + adc_b2.s2.c5)) +
	C2 * ((uint32_t)(adc_b2.s14.c5 + adc_b2.s3.c5)) +
	C3 * ((uint32_t)(adc_b2.s13.c5 + adc_b2.s4.c5)) +
	C4 * ((uint32_t)(adc_b2.s12.c5 + adc_b2.s5.c5)) +
	C5 * ((uint32_t)(adc_b2.s11.c5 + adc_b2.s6.c5)) +
	C6 * ((uint32_t)(adc_b2.s10.c5 + adc_b2.s7.c5)) +
	C7 * ((uint32_t)(adc_b2.s9.c5 + adc_b2.s8.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c0 + adc_b2.s5.c0)) +
	C1 * ((uint32_t)(adc_b0.s3.c0 + adc_b2.s6.c0)) +
	C2 * ((uint32_t)(adc_b0.s2.c0 + adc_b2.s7.c0)) +
	C3 * ((uint32_t)(adc_b0.s1.c0 + adc_b2.s8.c0)) +
	C4 * ((uint32_t)(adc_b0.s0.c0 + adc_b2.s9.c0)) +
	C5 * ((uint32_t)(adc_b2.s15.c0 + adc_b2.s10.c0)) +
	C6 * ((uint32_t)(adc_b2.s14.c0 + adc_b2.s11.c0)) +
	C7 * ((uint32_t)(adc_b2.s13.c0 + adc_b2.s12.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c1 + adc_b2.s5.c1)) +
	C1 * ((uint32_t)(adc_b0.s3.c1 + adc_b2.s6.c1)) +
	C2 * ((uint32_t)(adc_b0.s2.c1 + adc_b2.s7.c1)) +
	C3 * ((uint32_t)(adc_b0.s1.c1 + adc_b2.s8.c1)) +
	C4 * ((uint32_t)(adc_b0.s0.c1 + adc_b2.s9.c1)) +
	C5 * ((uint32_t)(adc_b2.s15.c1 + adc_b2.s10.c1)) +
	C6 * ((uint32_t)(adc_b2.s14.c1 + adc_b2.s11.c1)) +
	C7 * ((uint32_t)(adc_b2.s13.c1 + adc_b2.s12.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c2 + adc_b2.s5.c2)) +
	C1 * ((uint32_t)(adc_b0.s3.c2 + adc_b2.s6.c2)) +
	C2 * ((uint32_t)(adc_b0.s2.c2 + adc_b2.s7.c2)) +
	C3 * ((uint32_t)(adc_b0.s1.c2 + adc_b2.s8.c2)) +
	C4 * ((uint32_t)(adc_b0.s0.c2 + adc_b2.s9.c2)) +
	C5 * ((uint32_t)(adc_b2.s15.c2 + adc_b2.s10.c2)) +
	C6 * ((uint32_t)(adc_b2.s14.c2 + adc_b2.s11.c2)) +
	C7 * ((uint32_t)(adc_b2.s13.c2 + adc_b2.s12.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c3 + adc_b2.s5.c3)) +
	C1 * ((uint32_t)(adc_b0.s3.c3 + adc_b2.s6.c3)) +
	C2 * ((uint32_t)(adc_b0.s2.c3 + adc_b2.s7.c3)) +
	C3 * ((uint32_t)(adc_b0.s1.c3 + adc_b2.s8.c3)) +
	C4 * ((uint32_t)(adc_b0.s0.c3 + adc_b2.s9.c3)) +
	C5 * ((uint32_t)(adc_b2.s15.c3 + adc_b2.s10.c3)) +
	C6 * ((uint32_t)(adc_b2.s14.c3 + adc_b2.s11.c3)) +
	C7 * ((uint32_t)(adc_b2.s13.c3 + adc_b2.s12.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c4 + adc_b2.s5.c4)) +
	C1 * ((uint32_t)(adc_b0.s3.c4 + adc_b2.s6.c4)) +
	C2 * ((uint32_t)(adc_b0.s2.c4 + adc_b2.s7.c4)) +
	C3 * ((uint32_t)(adc_b0.s1.c4 + adc_b2.s8.c4)) +
	C4 * ((uint32_t)(adc_b0.s0.c4 + adc_b2.s9.c4)) +
	C5 * ((uint32_t)(adc_b2.s15.c4 + adc_b2.s10.c4)) +
	C6 * ((uint32_t)(adc_b2.s14.c4 + adc_b2.s11.c4)) +
	C7 * ((uint32_t)(adc_b2.s13.c4 + adc_b2.s12.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s4.c5 + adc_b2.s5.c5)) +
	C1 * ((uint32_t)(adc_b0.s3.c5 + adc_b2.s6.c5)) +
	C2 * ((uint32_t)(adc_b0.s2.c5 + adc_b2.s7.c5)) +
	C3 * ((uint32_t)(adc_b0.s1.c5 + adc_b2.s8.c5)) +
	C4 * ((uint32_t)(adc_b0.s0.c5 + adc_b2.s9.c5)) +
	C5 * ((uint32_t)(adc_b2.s15.c5 + adc_b2.s10.c5)) +
	C6 * ((uint32_t)(adc_b2.s14.c5 + adc_b2.s11.c5)) +
	C7 * ((uint32_t)(adc_b2.s13.c5 + adc_b2.s12.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c0 + adc_b2.s9.c0)) +
	C1 * ((uint32_t)(adc_b0.s7.c0 + adc_b2.s10.c0)) +
	C2 * ((uint32_t)(adc_b0.s6.c0 + adc_b2.s11.c0)) +
	C3 * ((uint32_t)(adc_b0.s5.c0 + adc_b2.s12.c0)) +
	C4 * ((uint32_t)(adc_b0.s4.c0 + adc_b2.s13.c0)) +
	C5 * ((uint32_t)(adc_b0.s3.c0 + adc_b2.s14.c0)) +
	C6 * ((uint32_t)(adc_b0.s2.c0 + adc_b2.s15.c0)) +
	C7 * ((uint32_t)(adc_b0.s1.c0 + adc_b0.s0.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c1 + adc_b2.s9.c1)) +
	C1 * ((uint32_t)(adc_b0.s7.c1 + adc_b2.s10.c1)) +
	C2 * ((uint32_t)(adc_b0.s6.c1 + adc_b2.s11.c1)) +
	C3 * ((uint32_t)(adc_b0.s5.c1 + adc_b2.s12.c1)) +
	C4 * ((uint32_t)(adc_b0.s4.c1 + adc_b2.s13.c1)) +
	C5 * ((uint32_t)(adc_b0.s3.c1 + adc_b2.s14.c1)) +
	C6 * ((uint32_t)(adc_b0.s2.c1 + adc_b2.s15.c1)) +
	C7 * ((uint32_t)(adc_b0.s1.c1 + adc_b0.s0.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c2 + adc_b2.s9.c2)) +
	C1 * ((uint32_t)(adc_b0.s7.c2 + adc_b2.s10.c2)) +
	C2 * ((uint32_t)(adc_b0.s6.c2 + adc_b2.s11.c2)) +
	C3 * ((uint32_t)(adc_b0.s5.c2 + adc_b2.s12.c2)) +
	C4 * ((uint32_t)(adc_b0.s4.c2 + adc_b2.s13.c2)) +
	C5 * ((uint32_t)(adc_b0.s3.c2 + adc_b2.s14.c2)) +
	C6 * ((uint32_t)(adc_b0.s2.c2 + adc_b2.s15.c2)) +
	C7 * ((uint32_t)(adc_b0.s1.c2 + adc_b0.s0.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c3 + adc_b2.s9.c3)) +
	C1 * ((uint32_t)(adc_b0.s7.c3 + adc_b2.s10.c3)) +
	C2 * ((uint32_t)(adc_b0.s6.c3 + adc_b2.s11.c3)) +
	C3 * ((uint32_t)(adc_b0.s5.c3 + adc_b2.s12.c3)) +
	C4 * ((uint32_t)(adc_b0.s4.c3 + adc_b2.s13.c3)) +
	C5 * ((uint32_t)(adc_b0.s3.c3 + adc_b2.s14.c3)) +
	C6 * ((uint32_t)(adc_b0.s2.c3 + adc_b2.s15.c3)) +
	C7 * ((uint32_t)(adc_b0.s1.c3 + adc_b0.s0.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c4 + adc_b2.s9.c4)) +
	C1 * ((uint32_t)(adc_b0.s7.c4 + adc_b2.s10.c4)) +
	C2 * ((uint32_t)(adc_b0.s6.c4 + adc_b2.s11.c4)) +
	C3 * ((uint32_t)(adc_b0.s5.c4 + adc_b2.s12.c4)) +
	C4 * ((uint32_t)(adc_b0.s4.c4 + adc_b2.s13.c4)) +
	C5 * ((uint32_t)(adc_b0.s3.c4 + adc_b2.s14.c4)) +
	C6 * ((uint32_t)(adc_b0.s2.c4 + adc_b2.s15.c4)) +
	C7 * ((uint32_t)(adc_b0.s1.c4 + adc_b0.s0.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s8.c5 + adc_b2.s9.c5)) +
	C1 * ((uint32_t)(adc_b0.s7.c5 + adc_b2.s10.c5)) +
	C2 * ((uint32_t)(adc_b0.s6.c5 + adc_b2.s11.c5)) +
	C3 * ((uint32_t)(adc_b0.s5.c5 + adc_b2.s12.c5)) +
	C4 * ((uint32_t)(adc_b0.s4.c5 + adc_b2.s13.c5)) +
	C5 * ((uint32_t)(adc_b0.s3.c5 + adc_b2.s14.c5)) +
	C6 * ((uint32_t)(adc_b0.s2.c5 + adc_b2.s15.c5)) +
	C7 * ((uint32_t)(adc_b0.s1.c5 + adc_b0.s0.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c0 + adc_b2.s13.c0)) +
	C1 * ((uint32_t)(adc_b0.s11.c0 + adc_b2.s14.c0)) +
	C2 * ((uint32_t)(adc_b0.s10.c0 + adc_b2.s15.c0)) +
	C3 * ((uint32_t)(adc_b0.s9.c0 + adc_b0.s0.c0)) +
	C4 * ((uint32_t)(adc_b0.s8.c0 + adc_b0.s1.c0)) +
	C5 * ((uint32_t)(adc_b0.s7.c0 + adc_b0.s2.c0)) +
	C6 * ((uint32_t)(adc_b0.s6.c0 + adc_b0.s3.c0)) +
	C7 * ((uint32_t)(adc_b0.s5.c0 + adc_b0.s4.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c1 + adc_b2.s13.c1)) +
	C1 * ((uint32_t)(adc_b0.s11.c1 + adc_b2.s14.c1)) +
	C2 * ((uint32_t)(adc_b0.s10.c1 + adc_b2.s15.c1)) +
	C3 * ((uint32_t)(adc_b0.s9.c1 + adc_b0.s0.c1)) +
	C4 * ((uint32_t)(adc_b0.s8.c1 + adc_b0.s1.c1)) +
	C5 * ((uint32_t)(adc_b0.s7.c1 + adc_b0.s2.c1)) +
	C6 * ((uint32_t)(adc_b0.s6.c1 + adc_b0.s3.c1)) +
	C7 * ((uint32_t)(adc_b0.s5.c1 + adc_b0.s4.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c2 + adc_b2.s13.c2)) +
	C1 * ((uint32_t)(adc_b0.s11.c2 + adc_b2.s14.c2)) +
	C2 * ((uint32_t)(adc_b0.s10.c2 + adc_b2.s15.c2)) +
	C3 * ((uint32_t)(adc_b0.s9.c2 + adc_b0.s0.c2)) +
	C4 * ((uint32_t)(adc_b0.s8.c2 + adc_b0.s1.c2)) +
	C5 * ((uint32_t)(adc_b0.s7.c2 + adc_b0.s2.c2)) +
	C6 * ((uint32_t)(adc_b0.s6.c2 + adc_b0.s3.c2)) +
	C7 * ((uint32_t)(adc_b0.s5.c2 + adc_b0.s4.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c3 + adc_b2.s13.c3)) +
	C1 * ((uint32_t)(adc_b0.s11.c3 + adc_b2.s14.c3)) +
	C2 * ((uint32_t)(adc_b0.s10.c3 + adc_b2.s15.c3)) +
	C3 * ((uint32_t)(adc_b0.s9.c3 + adc_b0.s0.c3)) +
	C4 * ((uint32_t)(adc_b0.s8.c3 + adc_b0.s1.c3)) +
	C5 * ((uint32_t)(adc_b0.s7.c3 + adc_b0.s2.c3)) +
	C6 * ((uint32_t)(adc_b0.s6.c3 + adc_b0.s3.c3)) +
	C7 * ((uint32_t)(adc_b0.s5.c3 + adc_b0.s4.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c4 + adc_b2.s13.c4)) +
	C1 * ((uint32_t)(adc_b0.s11.c4 + adc_b2.s14.c4)) +
	C2 * ((uint32_t)(adc_b0.s10.c4 + adc_b2.s15.c4)) +
	C3 * ((uint32_t)(adc_b0.s9.c4 + adc_b0.s0.c4)) +
	C4 * ((uint32_t)(adc_b0.s8.c4 + adc_b0.s1.c4)) +
	C5 * ((uint32_t)(adc_b0.s7.c4 + adc_b0.s2.c4)) +
	C6 * ((uint32_t)(adc_b0.s6.c4 + adc_b0.s3.c4)) +
	C7 * ((uint32_t)(adc_b0.s5.c4 + adc_b0.s4.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b0.s12.c5 + adc_b2.s13.c5)) +
	C1 * ((uint32_t)(adc_b0.s11.c5 + adc_b2.s14.c5)) +
	C2 * ((uint32_t)(adc_b0.s10.c5 + adc_b2.s15.c5)) +
	C3 * ((uint32_t)(adc_b0.s9.c5 + adc_b0.s0.c5)) +
	C4 * ((uint32_t)(adc_b0.s8.c5 + adc_b0.s1.c5)) +
	C5 * ((uint32_t)(adc_b0.s7.c5 + adc_b0.s2.c5)) +
	C6 * ((uint32_t)(adc_b0.s6.c5 + adc_b0.s3.c5)) +
	C7 * ((uint32_t)(adc_b0.s5.c5 + adc_b0.s4.c5)) ) >> 16);
} else if (bf_desc == BFD_1) {
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c0 + adc_b0.s1.c0)) +
	C1 * ((uint32_t)(adc_b0.s15.c0 + adc_b0.s2.c0)) +
	C2 * ((uint32_t)(adc_b0.s14.c0 + adc_b0.s3.c0)) +
	C3 * ((uint32_t)(adc_b0.s13.c0 + adc_b0.s4.c0)) +
	C4 * ((uint32_t)(adc_b0.s12.c0 + adc_b0.s5.c0)) +
	C5 * ((uint32_t)(adc_b0.s11.c0 + adc_b0.s6.c0)) +
	C6 * ((uint32_t)(adc_b0.s10.c0 + adc_b0.s7.c0)) +
	C7 * ((uint32_t)(adc_b0.s9.c0 + adc_b0.s8.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c1 + adc_b0.s1.c1)) +
	C1 * ((uint32_t)(adc_b0.s15.c1 + adc_b0.s2.c1)) +
	C2 * ((uint32_t)(adc_b0.s14.c1 + adc_b0.s3.c1)) +
	C3 * ((uint32_t)(adc_b0.s13.c1 + adc_b0.s4.c1)) +
	C4 * ((uint32_t)(adc_b0.s12.c1 + adc_b0.s5.c1)) +
	C5 * ((uint32_t)(adc_b0.s11.c1 + adc_b0.s6.c1)) +
	C6 * ((uint32_t)(adc_b0.s10.c1 + adc_b0.s7.c1)) +
	C7 * ((uint32_t)(adc_b0.s9.c1 + adc_b0.s8.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c2 + adc_b0.s1.c2)) +
	C1 * ((uint32_t)(adc_b0.s15.c2 + adc_b0.s2.c2)) +
	C2 * ((uint32_t)(adc_b0.s14.c2 + adc_b0.s3.c2)) +
	C3 * ((uint32_t)(adc_b0.s13.c2 + adc_b0.s4.c2)) +
	C4 * ((uint32_t)(adc_b0.s12.c2 + adc_b0.s5.c2)) +
	C5 * ((uint32_t)(adc_b0.s11.c2 + adc_b0.s6.c2)) +
	C6 * ((uint32_t)(adc_b0.s10.c2 + adc_b0.s7.c2)) +
	C7 * ((uint32_t)(adc_b0.s9.c2 + adc_b0.s8.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c3 + adc_b0.s1.c3)) +
	C1 * ((uint32_t)(adc_b0.s15.c3 + adc_b0.s2.c3)) +
	C2 * ((uint32_t)(adc_b0.s14.c3 + adc_b0.s3.c3)) +
	C3 * ((uint32_t)(adc_b0.s13.c3 + adc_b0.s4.c3)) +
	C4 * ((uint32_t)(adc_b0.s12.c3 + adc_b0.s5.c3)) +
	C5 * ((uint32_t)(adc_b0.s11.c3 + adc_b0.s6.c3)) +
	C6 * ((uint32_t)(adc_b0.s10.c3 + adc_b0.s7.c3)) +
	C7 * ((uint32_t)(adc_b0.s9.c3 + adc_b0.s8.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c4 + adc_b0.s1.c4)) +
	C1 * ((uint32_t)(adc_b0.s15.c4 + adc_b0.s2.c4)) +
	C2 * ((uint32_t)(adc_b0.s14.c4 + adc_b0.s3.c4)) +
	C3 * ((uint32_t)(adc_b0.s13.c4 + adc_b0.s4.c4)) +
	C4 * ((uint32_t)(adc_b0.s12.c4 + adc_b0.s5.c4)) +
	C5 * ((uint32_t)(adc_b0.s11.c4 + adc_b0.s6.c4)) +
	C6 * ((uint32_t)(adc_b0.s10.c4 + adc_b0.s7.c4)) +
	C7 * ((uint32_t)(adc_b0.s9.c4 + adc_b0.s8.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s0.c5 + adc_b0.s1.c5)) +
	C1 * ((uint32_t)(adc_b0.s15.c5 + adc_b0.s2.c5)) +
	C2 * ((uint32_t)(adc_b0.s14.c5 + adc_b0.s3.c5)) +
	C3 * ((uint32_t)(adc_b0.s13.c5 + adc_b0.s4.c5)) +
	C4 * ((uint32_t)(adc_b0.s12.c5 + adc_b0.s5.c5)) +
	C5 * ((uint32_t)(adc_b0.s11.c5 + adc_b0.s6.c5)) +
	C6 * ((uint32_t)(adc_b0.s10.c5 + adc_b0.s7.c5)) +
	C7 * ((uint32_t)(adc_b0.s9.c5 + adc_b0.s8.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c0 + adc_b0.s5.c0)) +
	C1 * ((uint32_t)(adc_b1.s3.c0 + adc_b0.s6.c0)) +
	C2 * ((uint32_t)(adc_b1.s2.c0 + adc_b0.s7.c0)) +
	C3 * ((uint32_t)(adc_b1.s1.c0 + adc_b0.s8.c0)) +
	C4 * ((uint32_t)(adc_b1.s0.c0 + adc_b0.s9.c0)) +
	C5 * ((uint32_t)(adc_b0.s15.c0 + adc_b0.s10.c0)) +
	C6 * ((uint32_t)(adc_b0.s14.c0 + adc_b0.s11.c0)) +
	C7 * ((uint32_t)(adc_b0.s13.c0 + adc_b0.s12.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c1 + adc_b0.s5.c1)) +
	C1 * ((uint32_t)(adc_b1.s3.c1 + adc_b0.s6.c1)) +
	C2 * ((uint32_t)(adc_b1.s2.c1 + adc_b0.s7.c1)) +
	C3 * ((uint32_t)(adc_b1.s1.c1 + adc_b0.s8.c1)) +
	C4 * ((uint32_t)(adc_b1.s0.c1 + adc_b0.s9.c1)) +
	C5 * ((uint32_t)(adc_b0.s15.c1 + adc_b0.s10.c1)) +
	C6 * ((uint32_t)(adc_b0.s14.c1 + adc_b0.s11.c1)) +
	C7 * ((uint32_t)(adc_b0.s13.c1 + adc_b0.s12.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c2 + adc_b0.s5.c2)) +
	C1 * ((uint32_t)(adc_b1.s3.c2 + adc_b0.s6.c2)) +
	C2 * ((uint32_t)(adc_b1.s2.c2 + adc_b0.s7.c2)) +
	C3 * ((uint32_t)(adc_b1.s1.c2 + adc_b0.s8.c2)) +
	C4 * ((uint32_t)(adc_b1.s0.c2 + adc_b0.s9.c2)) +
	C5 * ((uint32_t)(adc_b0.s15.c2 + adc_b0.s10.c2)) +
	C6 * ((uint32_t)(adc_b0.s14.c2 + adc_b0.s11.c2)) +
	C7 * ((uint32_t)(adc_b0.s13.c2 + adc_b0.s12.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c3 + adc_b0.s5.c3)) +
	C1 * ((uint32_t)(adc_b1.s3.c3 + adc_b0.s6.c3)) +
	C2 * ((uint32_t)(adc_b1.s2.c3 + adc_b0.s7.c3)) +
	C3 * ((uint32_t)(adc_b1.s1.c3 + adc_b0.s8.c3)) +
	C4 * ((uint32_t)(adc_b1.s0.c3 + adc_b0.s9.c3)) +
	C5 * ((uint32_t)(adc_b0.s15.c3 + adc_b0.s10.c3)) +
	C6 * ((uint32_t)(adc_b0.s14.c3 + adc_b0.s11.c3)) +
	C7 * ((uint32_t)(adc_b0.s13.c3 + adc_b0.s12.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c4 + adc_b0.s5.c4)) +
	C1 * ((uint32_t)(adc_b1.s3.c4 + adc_b0.s6.c4)) +
	C2 * ((uint32_t)(adc_b1.s2.c4 + adc_b0.s7.c4)) +
	C3 * ((uint32_t)(adc_b1.s1.c4 + adc_b0.s8.c4)) +
	C4 * ((uint32_t)(adc_b1.s0.c4 + adc_b0.s9.c4)) +
	C5 * ((uint32_t)(adc_b0.s15.c4 + adc_b0.s10.c4)) +
	C6 * ((uint32_t)(adc_b0.s14.c4 + adc_b0.s11.c4)) +
	C7 * ((uint32_t)(adc_b0.s13.c4 + adc_b0.s12.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s4.c5 + adc_b0.s5.c5)) +
	C1 * ((uint32_t)(adc_b1.s3.c5 + adc_b0.s6.c5)) +
	C2 * ((uint32_t)(adc_b1.s2.c5 + adc_b0.s7.c5)) +
	C3 * ((uint32_t)(adc_b1.s1.c5 + adc_b0.s8.c5)) +
	C4 * ((uint32_t)(adc_b1.s0.c5 + adc_b0.s9.c5)) +
	C5 * ((uint32_t)(adc_b0.s15.c5 + adc_b0.s10.c5)) +
	C6 * ((uint32_t)(adc_b0.s14.c5 + adc_b0.s11.c5)) +
	C7 * ((uint32_t)(adc_b0.s13.c5 + adc_b0.s12.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c0 + adc_b0.s9.c0)) +
	C1 * ((uint32_t)(adc_b1.s7.c0 + adc_b0.s10.c0)) +
	C2 * ((uint32_t)(adc_b1.s6.c0 + adc_b0.s11.c0)) +
	C3 * ((uint32_t)(adc_b1.s5.c0 + adc_b0.s12.c0)) +
	C4 * ((uint32_t)(adc_b1.s4.c0 + adc_b0.s13.c0)) +
	C5 * ((uint32_t)(adc_b1.s3.c0 + adc_b0.s14.c0)) +
	C6 * ((uint32_t)(adc_b1.s2.c0 + adc_b0.s15.c0)) +
	C7 * ((uint32_t)(adc_b1.s1.c0 + adc_b1.s0.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c1 + adc_b0.s9.c1)) +
	C1 * ((uint32_t)(adc_b1.s7.c1 + adc_b0.s10.c1)) +
	C2 * ((uint32_t)(adc_b1.s6.c1 + adc_b0.s11.c1)) +
	C3 * ((uint32_t)(adc_b1.s5.c1 + adc_b0.s12.c1)) +
	C4 * ((uint32_t)(adc_b1.s4.c1 + adc_b0.s13.c1)) +
	C5 * ((uint32_t)(adc_b1.s3.c1 + adc_b0.s14.c1)) +
	C6 * ((uint32_t)(adc_b1.s2.c1 + adc_b0.s15.c1)) +
	C7 * ((uint32_t)(adc_b1.s1.c1 + adc_b1.s0.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c2 + adc_b0.s9.c2)) +
	C1 * ((uint32_t)(adc_b1.s7.c2 + adc_b0.s10.c2)) +
	C2 * ((uint32_t)(adc_b1.s6.c2 + adc_b0.s11.c2)) +
	C3 * ((uint32_t)(adc_b1.s5.c2 + adc_b0.s12.c2)) +
	C4 * ((uint32_t)(adc_b1.s4.c2 + adc_b0.s13.c2)) +
	C5 * ((uint32_t)(adc_b1.s3.c2 + adc_b0.s14.c2)) +
	C6 * ((uint32_t)(adc_b1.s2.c2 + adc_b0.s15.c2)) +
	C7 * ((uint32_t)(adc_b1.s1.c2 + adc_b1.s0.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c3 + adc_b0.s9.c3)) +
	C1 * ((uint32_t)(adc_b1.s7.c3 + adc_b0.s10.c3)) +
	C2 * ((uint32_t)(adc_b1.s6.c3 + adc_b0.s11.c3)) +
	C3 * ((uint32_t)(adc_b1.s5.c3 + adc_b0.s12.c3)) +
	C4 * ((uint32_t)(adc_b1.s4.c3 + adc_b0.s13.c3)) +
	C5 * ((uint32_t)(adc_b1.s3.c3 + adc_b0.s14.c3)) +
	C6 * ((uint32_t)(adc_b1.s2.c3 + adc_b0.s15.c3)) +
	C7 * ((uint32_t)(adc_b1.s1.c3 + adc_b1.s0.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c4 + adc_b0.s9.c4)) +
	C1 * ((uint32_t)(adc_b1.s7.c4 + adc_b0.s10.c4)) +
	C2 * ((uint32_t)(adc_b1.s6.c4 + adc_b0.s11.c4)) +
	C3 * ((uint32_t)(adc_b1.s5.c4 + adc_b0.s12.c4)) +
	C4 * ((uint32_t)(adc_b1.s4.c4 + adc_b0.s13.c4)) +
	C5 * ((uint32_t)(adc_b1.s3.c4 + adc_b0.s14.c4)) +
	C6 * ((uint32_t)(adc_b1.s2.c4 + adc_b0.s15.c4)) +
	C7 * ((uint32_t)(adc_b1.s1.c4 + adc_b1.s0.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s8.c5 + adc_b0.s9.c5)) +
	C1 * ((uint32_t)(adc_b1.s7.c5 + adc_b0.s10.c5)) +
	C2 * ((uint32_t)(adc_b1.s6.c5 + adc_b0.s11.c5)) +
	C3 * ((uint32_t)(adc_b1.s5.c5 + adc_b0.s12.c5)) +
	C4 * ((uint32_t)(adc_b1.s4.c5 + adc_b0.s13.c5)) +
	C5 * ((uint32_t)(adc_b1.s3.c5 + adc_b0.s14.c5)) +
	C6 * ((uint32_t)(adc_b1.s2.c5 + adc_b0.s15.c5)) +
	C7 * ((uint32_t)(adc_b1.s1.c5 + adc_b1.s0.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c0 + adc_b0.s13.c0)) +
	C1 * ((uint32_t)(adc_b1.s11.c0 + adc_b0.s14.c0)) +
	C2 * ((uint32_t)(adc_b1.s10.c0 + adc_b0.s15.c0)) +
	C3 * ((uint32_t)(adc_b1.s9.c0 + adc_b1.s0.c0)) +
	C4 * ((uint32_t)(adc_b1.s8.c0 + adc_b1.s1.c0)) +
	C5 * ((uint32_t)(adc_b1.s7.c0 + adc_b1.s2.c0)) +
	C6 * ((uint32_t)(adc_b1.s6.c0 + adc_b1.s3.c0)) +
	C7 * ((uint32_t)(adc_b1.s5.c0 + adc_b1.s4.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c1 + adc_b0.s13.c1)) +
	C1 * ((uint32_t)(adc_b1.s11.c1 + adc_b0.s14.c1)) +
	C2 * ((uint32_t)(adc_b1.s10.c1 + adc_b0.s15.c1)) +
	C3 * ((uint32_t)(adc_b1.s9.c1 + adc_b1.s0.c1)) +
	C4 * ((uint32_t)(adc_b1.s8.c1 + adc_b1.s1.c1)) +
	C5 * ((uint32_t)(adc_b1.s7.c1 + adc_b1.s2.c1)) +
	C6 * ((uint32_t)(adc_b1.s6.c1 + adc_b1.s3.c1)) +
	C7 * ((uint32_t)(adc_b1.s5.c1 + adc_b1.s4.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c2 + adc_b0.s13.c2)) +
	C1 * ((uint32_t)(adc_b1.s11.c2 + adc_b0.s14.c2)) +
	C2 * ((uint32_t)(adc_b1.s10.c2 + adc_b0.s15.c2)) +
	C3 * ((uint32_t)(adc_b1.s9.c2 + adc_b1.s0.c2)) +
	C4 * ((uint32_t)(adc_b1.s8.c2 + adc_b1.s1.c2)) +
	C5 * ((uint32_t)(adc_b1.s7.c2 + adc_b1.s2.c2)) +
	C6 * ((uint32_t)(adc_b1.s6.c2 + adc_b1.s3.c2)) +
	C7 * ((uint32_t)(adc_b1.s5.c2 + adc_b1.s4.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c3 + adc_b0.s13.c3)) +
	C1 * ((uint32_t)(adc_b1.s11.c3 + adc_b0.s14.c3)) +
	C2 * ((uint32_t)(adc_b1.s10.c3 + adc_b0.s15.c3)) +
	C3 * ((uint32_t)(adc_b1.s9.c3 + adc_b1.s0.c3)) +
	C4 * ((uint32_t)(adc_b1.s8.c3 + adc_b1.s1.c3)) +
	C5 * ((uint32_t)(adc_b1.s7.c3 + adc_b1.s2.c3)) +
	C6 * ((uint32_t)(adc_b1.s6.c3 + adc_b1.s3.c3)) +
	C7 * ((uint32_t)(adc_b1.s5.c3 + adc_b1.s4.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c4 + adc_b0.s13.c4)) +
	C1 * ((uint32_t)(adc_b1.s11.c4 + adc_b0.s14.c4)) +
	C2 * ((uint32_t)(adc_b1.s10.c4 + adc_b0.s15.c4)) +
	C3 * ((uint32_t)(adc_b1.s9.c4 + adc_b1.s0.c4)) +
	C4 * ((uint32_t)(adc_b1.s8.c4 + adc_b1.s1.c4)) +
	C5 * ((uint32_t)(adc_b1.s7.c4 + adc_b1.s2.c4)) +
	C6 * ((uint32_t)(adc_b1.s6.c4 + adc_b1.s3.c4)) +
	C7 * ((uint32_t)(adc_b1.s5.c4 + adc_b1.s4.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b1.s12.c5 + adc_b0.s13.c5)) +
	C1 * ((uint32_t)(adc_b1.s11.c5 + adc_b0.s14.c5)) +
	C2 * ((uint32_t)(adc_b1.s10.c5 + adc_b0.s15.c5)) +
	C3 * ((uint32_t)(adc_b1.s9.c5 + adc_b1.s0.c5)) +
	C4 * ((uint32_t)(adc_b1.s8.c5 + adc_b1.s1.c5)) +
	C5 * ((uint32_t)(adc_b1.s7.c5 + adc_b1.s2.c5)) +
	C6 * ((uint32_t)(adc_b1.s6.c5 + adc_b1.s3.c5)) +
	C7 * ((uint32_t)(adc_b1.s5.c5 + adc_b1.s4.c5)) ) >> 16);
} else if (bf_desc == BFD_2) {
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c0 + adc_b1.s1.c0)) +
	C1 * ((uint32_t)(adc_b1.s15.c0 + adc_b1.s2.c0)) +
	C2 * ((uint32_t)(adc_b1.s14.c0 + adc_b1.s3.c0)) +
	C3 * ((uint32_t)(adc_b1.s13.c0 + adc_b1.s4.c0)) +
	C4 * ((uint32_t)(adc_b1.s12.c0 + adc_b1.s5.c0)) +
	C5 * ((uint32_t)(adc_b1.s11.c0 + adc_b1.s6.c0)) +
	C6 * ((uint32_t)(adc_b1.s10.c0 + adc_b1.s7.c0)) +
	C7 * ((uint32_t)(adc_b1.s9.c0 + adc_b1.s8.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c1 + adc_b1.s1.c1)) +
	C1 * ((uint32_t)(adc_b1.s15.c1 + adc_b1.s2.c1)) +
	C2 * ((uint32_t)(adc_b1.s14.c1 + adc_b1.s3.c1)) +
	C3 * ((uint32_t)(adc_b1.s13.c1 + adc_b1.s4.c1)) +
	C4 * ((uint32_t)(adc_b1.s12.c1 + adc_b1.s5.c1)) +
	C5 * ((uint32_t)(adc_b1.s11.c1 + adc_b1.s6.c1)) +
	C6 * ((uint32_t)(adc_b1.s10.c1 + adc_b1.s7.c1)) +
	C7 * ((uint32_t)(adc_b1.s9.c1 + adc_b1.s8.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c2 + adc_b1.s1.c2)) +
	C1 * ((uint32_t)(adc_b1.s15.c2 + adc_b1.s2.c2)) +
	C2 * ((uint32_t)(adc_b1.s14.c2 + adc_b1.s3.c2)) +
	C3 * ((uint32_t)(adc_b1.s13.c2 + adc_b1.s4.c2)) +
	C4 * ((uint32_t)(adc_b1.s12.c2 + adc_b1.s5.c2)) +
	C5 * ((uint32_t)(adc_b1.s11.c2 + adc_b1.s6.c2)) +
	C6 * ((uint32_t)(adc_b1.s10.c2 + adc_b1.s7.c2)) +
	C7 * ((uint32_t)(adc_b1.s9.c2 + adc_b1.s8.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c3 + adc_b1.s1.c3)) +
	C1 * ((uint32_t)(adc_b1.s15.c3 + adc_b1.s2.c3)) +
	C2 * ((uint32_t)(adc_b1.s14.c3 + adc_b1.s3.c3)) +
	C3 * ((uint32_t)(adc_b1.s13.c3 + adc_b1.s4.c3)) +
	C4 * ((uint32_t)(adc_b1.s12.c3 + adc_b1.s5.c3)) +
	C5 * ((uint32_t)(adc_b1.s11.c3 + adc_b1.s6.c3)) +
	C6 * ((uint32_t)(adc_b1.s10.c3 + adc_b1.s7.c3)) +
	C7 * ((uint32_t)(adc_b1.s9.c3 + adc_b1.s8.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c4 + adc_b1.s1.c4)) +
	C1 * ((uint32_t)(adc_b1.s15.c4 + adc_b1.s2.c4)) +
	C2 * ((uint32_t)(adc_b1.s14.c4 + adc_b1.s3.c4)) +
	C3 * ((uint32_t)(adc_b1.s13.c4 + adc_b1.s4.c4)) +
	C4 * ((uint32_t)(adc_b1.s12.c4 + adc_b1.s5.c4)) +
	C5 * ((uint32_t)(adc_b1.s11.c4 + adc_b1.s6.c4)) +
	C6 * ((uint32_t)(adc_b1.s10.c4 + adc_b1.s7.c4)) +
	C7 * ((uint32_t)(adc_b1.s9.c4 + adc_b1.s8.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s0.c5 + adc_b1.s1.c5)) +
	C1 * ((uint32_t)(adc_b1.s15.c5 + adc_b1.s2.c5)) +
	C2 * ((uint32_t)(adc_b1.s14.c5 + adc_b1.s3.c5)) +
	C3 * ((uint32_t)(adc_b1.s13.c5 + adc_b1.s4.c5)) +
	C4 * ((uint32_t)(adc_b1.s12.c5 + adc_b1.s5.c5)) +
	C5 * ((uint32_t)(adc_b1.s11.c5 + adc_b1.s6.c5)) +
	C6 * ((uint32_t)(adc_b1.s10.c5 + adc_b1.s7.c5)) +
	C7 * ((uint32_t)(adc_b1.s9.c5 + adc_b1.s8.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c0 + adc_b1.s5.c0)) +
	C1 * ((uint32_t)(adc_b2.s3.c0 + adc_b1.s6.c0)) +
	C2 * ((uint32_t)(adc_b2.s2.c0 + adc_b1.s7.c0)) +
	C3 * ((uint32_t)(adc_b2.s1.c0 + adc_b1.s8.c0)) +
	C4 * ((uint32_t)(adc_b2.s0.c0 + adc_b1.s9.c0)) +
	C5 * ((uint32_t)(adc_b1.s15.c0 + adc_b1.s10.c0)) +
	C6 * ((uint32_t)(adc_b1.s14.c0 + adc_b1.s11.c0)) +
	C7 * ((uint32_t)(adc_b1.s13.c0 + adc_b1.s12.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c1 + adc_b1.s5.c1)) +
	C1 * ((uint32_t)(adc_b2.s3.c1 + adc_b1.s6.c1)) +
	C2 * ((uint32_t)(adc_b2.s2.c1 + adc_b1.s7.c1)) +
	C3 * ((uint32_t)(adc_b2.s1.c1 + adc_b1.s8.c1)) +
	C4 * ((uint32_t)(adc_b2.s0.c1 + adc_b1.s9.c1)) +
	C5 * ((uint32_t)(adc_b1.s15.c1 + adc_b1.s10.c1)) +
	C6 * ((uint32_t)(adc_b1.s14.c1 + adc_b1.s11.c1)) +
	C7 * ((uint32_t)(adc_b1.s13.c1 + adc_b1.s12.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c2 + adc_b1.s5.c2)) +
	C1 * ((uint32_t)(adc_b2.s3.c2 + adc_b1.s6.c2)) +
	C2 * ((uint32_t)(adc_b2.s2.c2 + adc_b1.s7.c2)) +
	C3 * ((uint32_t)(adc_b2.s1.c2 + adc_b1.s8.c2)) +
	C4 * ((uint32_t)(adc_b2.s0.c2 + adc_b1.s9.c2)) +
	C5 * ((uint32_t)(adc_b1.s15.c2 + adc_b1.s10.c2)) +
	C6 * ((uint32_t)(adc_b1.s14.c2 + adc_b1.s11.c2)) +
	C7 * ((uint32_t)(adc_b1.s13.c2 + adc_b1.s12.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c3 + adc_b1.s5.c3)) +
	C1 * ((uint32_t)(adc_b2.s3.c3 + adc_b1.s6.c3)) +
	C2 * ((uint32_t)(adc_b2.s2.c3 + adc_b1.s7.c3)) +
	C3 * ((uint32_t)(adc_b2.s1.c3 + adc_b1.s8.c3)) +
	C4 * ((uint32_t)(adc_b2.s0.c3 + adc_b1.s9.c3)) +
	C5 * ((uint32_t)(adc_b1.s15.c3 + adc_b1.s10.c3)) +
	C6 * ((uint32_t)(adc_b1.s14.c3 + adc_b1.s11.c3)) +
	C7 * ((uint32_t)(adc_b1.s13.c3 + adc_b1.s12.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c4 + adc_b1.s5.c4)) +
	C1 * ((uint32_t)(adc_b2.s3.c4 + adc_b1.s6.c4)) +
	C2 * ((uint32_t)(adc_b2.s2.c4 + adc_b1.s7.c4)) +
	C3 * ((uint32_t)(adc_b2.s1.c4 + adc_b1.s8.c4)) +
	C4 * ((uint32_t)(adc_b2.s0.c4 + adc_b1.s9.c4)) +
	C5 * ((uint32_t)(adc_b1.s15.c4 + adc_b1.s10.c4)) +
	C6 * ((uint32_t)(adc_b1.s14.c4 + adc_b1.s11.c4)) +
	C7 * ((uint32_t)(adc_b1.s13.c4 + adc_b1.s12.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s4.c5 + adc_b1.s5.c5)) +
	C1 * ((uint32_t)(adc_b2.s3.c5 + adc_b1.s6.c5)) +
	C2 * ((uint32_t)(adc_b2.s2.c5 + adc_b1.s7.c5)) +
	C3 * ((uint32_t)(adc_b2.s1.c5 + adc_b1.s8.c5)) +
	C4 * ((uint32_t)(adc_b2.s0.c5 + adc_b1.s9.c5)) +
	C5 * ((uint32_t)(adc_b1.s15.c5 + adc_b1.s10.c5)) +
	C6 * ((uint32_t)(adc_b1.s14.c5 + adc_b1.s11.c5)) +
	C7 * ((uint32_t)(adc_b1.s13.c5 + adc_b1.s12.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c0 + adc_b1.s9.c0)) +
	C1 * ((uint32_t)(adc_b2.s7.c0 + adc_b1.s10.c0)) +
	C2 * ((uint32_t)(adc_b2.s6.c0 + adc_b1.s11.c0)) +
	C3 * ((uint32_t)(adc_b2.s5.c0 + adc_b1.s12.c0)) +
	C4 * ((uint32_t)(adc_b2.s4.c0 + adc_b1.s13.c0)) +
	C5 * ((uint32_t)(adc_b2.s3.c0 + adc_b1.s14.c0)) +
	C6 * ((uint32_t)(adc_b2.s2.c0 + adc_b1.s15.c0)) +
	C7 * ((uint32_t)(adc_b2.s1.c0 + adc_b2.s0.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c1 + adc_b1.s9.c1)) +
	C1 * ((uint32_t)(adc_b2.s7.c1 + adc_b1.s10.c1)) +
	C2 * ((uint32_t)(adc_b2.s6.c1 + adc_b1.s11.c1)) +
	C3 * ((uint32_t)(adc_b2.s5.c1 + adc_b1.s12.c1)) +
	C4 * ((uint32_t)(adc_b2.s4.c1 + adc_b1.s13.c1)) +
	C5 * ((uint32_t)(adc_b2.s3.c1 + adc_b1.s14.c1)) +
	C6 * ((uint32_t)(adc_b2.s2.c1 + adc_b1.s15.c1)) +
	C7 * ((uint32_t)(adc_b2.s1.c1 + adc_b2.s0.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c2 + adc_b1.s9.c2)) +
	C1 * ((uint32_t)(adc_b2.s7.c2 + adc_b1.s10.c2)) +
	C2 * ((uint32_t)(adc_b2.s6.c2 + adc_b1.s11.c2)) +
	C3 * ((uint32_t)(adc_b2.s5.c2 + adc_b1.s12.c2)) +
	C4 * ((uint32_t)(adc_b2.s4.c2 + adc_b1.s13.c2)) +
	C5 * ((uint32_t)(adc_b2.s3.c2 + adc_b1.s14.c2)) +
	C6 * ((uint32_t)(adc_b2.s2.c2 + adc_b1.s15.c2)) +
	C7 * ((uint32_t)(adc_b2.s1.c2 + adc_b2.s0.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c3 + adc_b1.s9.c3)) +
	C1 * ((uint32_t)(adc_b2.s7.c3 + adc_b1.s10.c3)) +
	C2 * ((uint32_t)(adc_b2.s6.c3 + adc_b1.s11.c3)) +
	C3 * ((uint32_t)(adc_b2.s5.c3 + adc_b1.s12.c3)) +
	C4 * ((uint32_t)(adc_b2.s4.c3 + adc_b1.s13.c3)) +
	C5 * ((uint32_t)(adc_b2.s3.c3 + adc_b1.s14.c3)) +
	C6 * ((uint32_t)(adc_b2.s2.c3 + adc_b1.s15.c3)) +
	C7 * ((uint32_t)(adc_b2.s1.c3 + adc_b2.s0.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c4 + adc_b1.s9.c4)) +
	C1 * ((uint32_t)(adc_b2.s7.c4 + adc_b1.s10.c4)) +
	C2 * ((uint32_t)(adc_b2.s6.c4 + adc_b1.s11.c4)) +
	C3 * ((uint32_t)(adc_b2.s5.c4 + adc_b1.s12.c4)) +
	C4 * ((uint32_t)(adc_b2.s4.c4 + adc_b1.s13.c4)) +
	C5 * ((uint32_t)(adc_b2.s3.c4 + adc_b1.s14.c4)) +
	C6 * ((uint32_t)(adc_b2.s2.c4 + adc_b1.s15.c4)) +
	C7 * ((uint32_t)(adc_b2.s1.c4 + adc_b2.s0.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s8.c5 + adc_b1.s9.c5)) +
	C1 * ((uint32_t)(adc_b2.s7.c5 + adc_b1.s10.c5)) +
	C2 * ((uint32_t)(adc_b2.s6.c5 + adc_b1.s11.c5)) +
	C3 * ((uint32_t)(adc_b2.s5.c5 + adc_b1.s12.c5)) +
	C4 * ((uint32_t)(adc_b2.s4.c5 + adc_b1.s13.c5)) +
	C5 * ((uint32_t)(adc_b2.s3.c5 + adc_b1.s14.c5)) +
	C6 * ((uint32_t)(adc_b2.s2.c5 + adc_b1.s15.c5)) +
	C7 * ((uint32_t)(adc_b2.s1.c5 + adc_b2.s0.c5)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c0 + adc_b1.s13.c0)) +
	C1 * ((uint32_t)(adc_b2.s11.c0 + adc_b1.s14.c0)) +
	C2 * ((uint32_t)(adc_b2.s10.c0 + adc_b1.s15.c0)) +
	C3 * ((uint32_t)(adc_b2.s9.c0 + adc_b2.s0.c0)) +
	C4 * ((uint32_t)(adc_b2.s8.c0 + adc_b2.s1.c0)) +
	C5 * ((uint32_t)(adc_b2.s7.c0 + adc_b2.s2.c0)) +
	C6 * ((uint32_t)(adc_b2.s6.c0 + adc_b2.s3.c0)) +
	C7 * ((uint32_t)(adc_b2.s5.c0 + adc_b2.s4.c0)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c1 + adc_b1.s13.c1)) +
	C1 * ((uint32_t)(adc_b2.s11.c1 + adc_b1.s14.c1)) +
	C2 * ((uint32_t)(adc_b2.s10.c1 + adc_b1.s15.c1)) +
	C3 * ((uint32_t)(adc_b2.s9.c1 + adc_b2.s0.c1)) +
	C4 * ((uint32_t)(adc_b2.s8.c1 + adc_b2.s1.c1)) +
	C5 * ((uint32_t)(adc_b2.s7.c1 + adc_b2.s2.c1)) +
	C6 * ((uint32_t)(adc_b2.s6.c1 + adc_b2.s3.c1)) +
	C7 * ((uint32_t)(adc_b2.s5.c1 + adc_b2.s4.c1)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c2 + adc_b1.s13.c2)) +
	C1 * ((uint32_t)(adc_b2.s11.c2 + adc_b1.s14.c2)) +
	C2 * ((uint32_t)(adc_b2.s10.c2 + adc_b1.s15.c2)) +
	C3 * ((uint32_t)(adc_b2.s9.c2 + adc_b2.s0.c2)) +
	C4 * ((uint32_t)(adc_b2.s8.c2 + adc_b2.s1.c2)) +
	C5 * ((uint32_t)(adc_b2.s7.c2 + adc_b2.s2.c2)) +
	C6 * ((uint32_t)(adc_b2.s6.c2 + adc_b2.s3.c2)) +
	C7 * ((uint32_t)(adc_b2.s5.c2 + adc_b2.s4.c2)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c3 + adc_b1.s13.c3)) +
	C1 * ((uint32_t)(adc_b2.s11.c3 + adc_b1.s14.c3)) +
	C2 * ((uint32_t)(adc_b2.s10.c3 + adc_b1.s15.c3)) +
	C3 * ((uint32_t)(adc_b2.s9.c3 + adc_b2.s0.c3)) +
	C4 * ((uint32_t)(adc_b2.s8.c3 + adc_b2.s1.c3)) +
	C5 * ((uint32_t)(adc_b2.s7.c3 + adc_b2.s2.c3)) +
	C6 * ((uint32_t)(adc_b2.s6.c3 + adc_b2.s3.c3)) +
	C7 * ((uint32_t)(adc_b2.s5.c3 + adc_b2.s4.c3)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c4 + adc_b1.s13.c4)) +
	C1 * ((uint32_t)(adc_b2.s11.c4 + adc_b1.s14.c4)) +
	C2 * ((uint32_t)(adc_b2.s10.c4 + adc_b1.s15.c4)) +
	C3 * ((uint32_t)(adc_b2.s9.c4 + adc_b2.s0.c4)) +
	C4 * ((uint32_t)(adc_b2.s8.c4 + adc_b2.s1.c4)) +
	C5 * ((uint32_t)(adc_b2.s7.c4 + adc_b2.s2.c4)) +
	C6 * ((uint32_t)(adc_b2.s6.c4 + adc_b2.s3.c4)) +
	C7 * ((uint32_t)(adc_b2.s5.c4 + adc_b2.s4.c4)) ) >> 16);
	*output_pointer++ = (uint16_t)((
	C0 * ((uint32_t)(adc_b2.s12.c5 + adc_b1.s13.c5)) +
	C1 * ((uint32_t)(adc_b2.s11.c5 + adc_b1.s14.c5)) +
	C2 * ((uint32_t)(adc_b2.s10.c5 + adc_b1.s15.c5)) +
	C3 * ((uint32_t)(adc_b2.s9.c5 + adc_b2.s0.c5)) +
	C4 * ((uint32_t)(adc_b2.s8.c5 + adc_b2.s1.c5)) +
	C5 * ((uint32_t)(adc_b2.s7.c5 + adc_b2.s2.c5)) +
	C6 * ((uint32_t)(adc_b2.s6.c5 + adc_b2.s3.c5)) +
	C7 * ((uint32_t)(adc_b2.s5.c5 + adc_b2.s4.c5)) ) >> 16);
}
