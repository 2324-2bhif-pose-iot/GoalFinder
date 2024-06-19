<template>
	<!-- progress bar -->
	<div class="col-12 mt-3 mb-2 pt-2 p-centered">
		<div class="col-2 mt-3 mb-2 col-sm-7 col-md-4 text-right p-centered">
			<div class="text-large text-left" v-if="msg !== null">{{ msg }}</div>
			<div class="bar mt-3 bar-sm">
				<div class="bar-item" :style="{ width: progress+'%' }" />
			</div>
			<div class="pt-2">{{progress}}%</div>
		</div>
	</div>
</template>

<script>
export default {
	name: 'ProgressBarPanel',
	props: {
		progress: {
			type: Number,
			default: 0,
		},
		msg: {
			type: String,
			default: null,
		},
	},
};
</script>

<style scoped>
</style>
