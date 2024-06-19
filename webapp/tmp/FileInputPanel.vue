
<template>
	<!-- panel file input -->
	<div class="form-group pt-2 mt-3">
		<label class="form-label col-2 col-md-2 col-sm-3" for="fileIp">{{label}}</label>
		<input id="fileIp" class="form-input file-input col-10 col-md-10 col-sm-9" type="file" ref="file" :data-type="type" :accept="accept" @change="onChange">
	</div>
</template>

<script>
export default {
	name: 'FileInputPanel',
	props: {
		label: {
			type: String,
			default: null,
		},
		type: {
			type: String,
			default: '',
		},
		accept: {
			type: String,
			default: '*',
		},
		onChange: {
			type: Function,
			default() {},
		},
	},
};
</script>

<style scoped>
</style>
