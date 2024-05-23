<template>
  <div>
    <div id="vb">
      <label for="sensitivity">Set Sensitivity of vibrationsensor: </label>
      <input
          type="range"
          v-model="sensitivity"
          id="sensitivity"
          min="1"
          max="100"
      />
      <span>{{ sensitivity }}</span>
      <Button @click="setSensitivity">Set</Button>
      <transition name="fade">
        <div v-if="message" class="message">{{ message }}</div>
      </transition>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      sensitivity: 50, // default sensitivity value
      message: '', // message to display
    };
  },
  methods: {
    setSensitivity() {
      this.message = `Sensitivity set to: ${this.sensitivity}`;
      console.log(this.message);
      setTimeout(() => {
        this.message = '';
      }, 3000); // Alert message will disappear after 3 seconds
    },
  },
};
</script>

<style scoped>
input[type="range"] {
  width: 300px;
  margin-right: 10px;
}

button:hover {
  background-color: #45a049;
}

button {
  float: right;
  margin-top: -1rem;
}

#vb {
  margin-top: 3rem;
}

.message {
  margin-top: 10px;
  padding: 10px;
  background-color: #e7f3e7;
  color: #2c662d;
  border: 1px solid #2c662d;
  border-radius: 5px;
  opacity: 1;
  transition: opacity 0.5s ease-in-out;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.5s;
}

.fade-enter,
.fade-leave-to /* .fade-leave-active in <2.1.8 */ {
  opacity: 0;
}
</style>
