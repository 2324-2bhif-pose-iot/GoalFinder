<template>
	<!-- result panel with action slot
		kind:
			'error':  Shows an error message
			'sucees': Shows a success message
	-->
	<div class="col-12 mt-3 pt-2 p-centered" :key="kind">
		<div class="col-3 col-sm-9 col-md-6 p-centered text-center">
			<svg-sign :kind="kind" />
			<span style="vertical-align: middle;" class="ml-2"> {{ msg }} </span>
			<div class="mt-5">
				<slot name="actions" />
			</div>
		</div>
	</div>
</template>

<script>
import SvgSign          from './SvgSign.vue';

export default {
	name: 'ResultPanel',
	props: {
		kind: {
			type: String,
			default: 'success',
		},
		msg: {
			type: String,
			default: '',
		},
	},
	components: {
		SvgSign,
	},
};
</script>

<style scoped>
</style>
