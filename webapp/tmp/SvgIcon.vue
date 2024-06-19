<!-- eslint-disable max-len -->

<template>
	<!-- various icons in SVG format
		kind:
			'back-arrow': Back arrow icon
			'refresh':    Clockwise circular arrow icon
	-->
	<svg xmlns="http://www.w3.org/2000/svg" class="pt-1" :width="size" :height="size"
			:style="style" viewBox="0 0 24 24" version="1.1">
		<!-- <g data-name="Layer 2"> -->
			<g :data-name="kind">
				<rect width="24" height="24" opacity="0" />
				<path
					v-if="kind === 'back-arrow'"
					fill="currentColor"
					d="M19 11H7.14l3.63-4.36a1 1 0 1 0-1.54-1.28l-5 6a1.19 1.19 0 0 0-.09.15c0 .05 0 .08-.07.13A1 1 0 0 0 4 12a1 1 0 0 0 .07.36c0 .05 0 .08.07.13a1.19 1.19 0 0 0 .09.15l5 6A1 1 0 0 0 10 19a1 1 0 0 0 .64-.23 1 1 0 0 0 .13-1.41L7.14 13H19a1 1 0 0 0 0-2z" />
				<path
					v-else-if="kind === 'refresh'"
					fill="currentColor"
					d="M20.3 13.43a1 1 0 0 0-1.25.65A7.14 7.14 0 0 1 12.18 19 7.1 7.1 0 0 1 5 12a7.1 7.1 0 0 1 7.18-7 7.26 7.26 0 0 1 4.65 1.67l-2.17-.36a1 1 0 0 0-1.15.83 1 1 0 0 0 .83 1.15l4.24.7h.17a1 1 0 0 0 .34-.06.33.33 0 0 0 .1-.06.78.78 0 0 0 .2-.11l.09-.11c0-.05.09-.09.13-.15s0-.1.05-.14a1.34 1.34 0 0 0 .07-.18l.75-4a1 1 0 0 0-2-.38l-.27 1.45A9.21 9.21 0 0 0 12.18 3 9.1 9.1 0 0 0 3 12a9.1 9.1 0 0 0 9.18 9A9.12 9.12 0 0 0 21 14.68a1 1 0 0 0-.7-1.25z" />
			</g>
		<!-- </g> -->
	</svg>
</template>

<script>
export default {
	name: 'SvgIcon',
	props: {
		kind: {
			type: String,
			default: '',
		},
		style: {
			type: String,
			default: '',
		},
		size: {
			type: String,
			default: '16px',
		},
	},
};
</script>

<style scoped>
</style>
