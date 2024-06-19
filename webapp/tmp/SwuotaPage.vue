<template>
	<!-- eslint-disable max-len -->
	<div  class="col-12 mt-1">
		<!-- action panel -->
		<transition name="fade" mode="out-in">
			<!-- result panel -->
			<result-panel :kind="updateResult" :msg="resultMsg" v-if="!loading && !uploading && updateResult != ''">
				<template v-slot:actions>
					<panel-btn-back-left :primary="updateResult === 'success'" :onClick="clear" />
					<panel-btn-refresh-left :primary="true" :onClick="retryUpload" v-if="updateResult === 'error'"/>
				</template>
			</result-panel>
		</transition>
		<transition name="fade" mode="out-in">
			<div class="col-12 p-centered" v-if="!loading && !uploading && updateResult == ''" key="otainput">
				<div class="form-horizontal p-centered">
					<span>Updates the software of the device.</span>
					<br />
					<span>The update starts automatically after a file is chosen.</span>
					<file-input-panel label="Firmware" type="firmware" accept=".bin,.bin.gz" :onChange="upload"/>
					<file-input-panel label="Filesystem" type="filesystem" accept=".bin,.bin.gz" :onChange="upload"/>
				</div>
			</div>
		</transition>
		<!-- upload progress panel -->
		<transition name="fade" mode="out-in">
			<progress-bar-panel :progress="progress" msg="Upload in progress ..." v-if="!loading && uploading" />
		</transition>
	</div>
</template>

<script>
import FileInputPanel           from '../cmps/FileInputPanel.vue';
import ProgressBarPanel         from '../cmps/ProgressBarPanel.vue';
import ResultPanel              from '../cmps/ResultPanel.vue';

import PanelBtnBackLeft         from '../cmps/ui/PanelBtnBackLeft.vue';
import PanelBtnRefreshLeft      from '../cmps/ui/PanelBtnRefreshLeft.vue';

export default {
	name: 'SwuotaPage',

	components: {
		FileInputPanel,
		ProgressBarPanel,
		ResultPanel,

		PanelBtnBackLeft,
		PanelBtnRefreshLeft,
	},

	data() {
		return {
			uris: {
				update: '/update',
			},
			loading: false,
			uploading: false,
			progress: 0,
			updateResult: '',
			resultMsg: null,

			type: 'unknown',
			file: null,
		};
	},

	methods: {
		fileMD5(file) {
			return new Promise((resolve, reject) => {
				const blobSlice = File.prototype.slice
					|| File.prototype.mozSlice || File.prototype.webkitSlice;
				const chunkSize = 2097152; // Read in chunks of 2MB
				const chunks = Math.ceil(file.size / chunkSize);
				const spark = new this.SparkMD5.ArrayBuffer();
				const fileReader = new FileReader();
				let currentChunk = 0;
				let loadNext;

				fileReader.onload = (e) => {
					spark.append(e.target.result); // Append array buffer
					currentChunk += 1;

					if (currentChunk < chunks) {
						loadNext();
					} else {
						const md5 = spark.end();
						resolve(md5);
					}
				};

				fileReader.onerror = (e) => {
					reject(e);
				};

				loadNext = () => {
					const start = currentChunk * chunkSize;
					const end = ((start + chunkSize) >= file.size) ? file.size : start + chunkSize;
					fileReader.readAsArrayBuffer(blobSlice.call(file, start, end));
				};

				loadNext();
			});
		},

		upload(event) {
			this.uploading = true;
			const formData = new FormData();
			if (event !== null) {
				[this.file] = event.target.files;
				this.type = event.target.dataset.type;
			}
			const request = new XMLHttpRequest();

			request.addEventListener('load', () => {
				if (request.status === 200) {
					this.resetUpload('success', 'Device is sucessfully updated');
				} else if (request.status !== 500) {
					this.resetUpload('error', `[HTTP ERROR] ${request.statusText}`);
				} else {
					this.resetUpload('error', request.responseText);
				}
			});

			// Upload progress
			request.upload.addEventListener('progress', (e) => {
				this.progress = Math.trunc((e.loaded / e.total) * 100);
			});

			request.withCredentials = true;

			this.fileMD5(this.file)
				.then((md5) => {
					formData.append('MD5', md5);
					formData.append(this.type, this.file, this.type);
					request.open('post', this.uris.update);
					request.send(formData);
				})
				.catch(() => {
					this.resetUpload('error', 'Unknown error while upload, check the console for details.');
				});
		},

		retryUpload() {
			this.clear();
			this.uploadOTA(null);
		},

		clear() {
			this.resetUpload('', null);
		},

		resetUpload(updateResult, resultMsg) {
			this.resultMsg = resultMsg;
			this.updateResult = updateResult;
			this.uploading = false;
			this.progress = 0;
		},
	},

	mounted() {
		console.log('Mounted SWutoa page');
	},
};
</script>

<style scoped lang="scss">
</style>
