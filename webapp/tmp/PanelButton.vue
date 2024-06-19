<template>
	<!-- panel button with icon slot -->
	<button :class="'btn btn-light mr-2' + (primary ? ' btn-primary' : '')" @click="onClick">
		<slot name="icon-left" />
		{{ label }}
		<slot name="icon-right" />
	</button>
</template>

<script>
export default {
	name: 'PanelButton',
	props: {
		label: {
			type: String,
			default: 'Button',
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
};
</script>

<style scoped>
</style>
