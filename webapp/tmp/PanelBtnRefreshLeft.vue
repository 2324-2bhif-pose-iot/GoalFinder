<template>
	<!-- panel button with back icon left to the text -->
	<panel-button :label="label" :primary="primary" :onClick="onClick">
		<template v-slot:icon-left>
			<svg-icon :primary="true" kind="refresh" size="16px"/>
		</template>
	</panel-button>
</template>

<script>

import PanelButton      from '../PanelButton.vue';
import SvgIcon          from '../SvgIcon.vue';

export default {
	name: 'PanelBtnBackLeft',
	props: {
		label: {
			type: String,
			default: 'Refresh',
		},
		primary: {
			type: Boolean,
			default: false,
		},
		onClick: {
			type: Function,
			default() {},
		},
	},
	components: {
		PanelButton,
		SvgIcon,
	},
};
</script>

<style scoped>
</style>
