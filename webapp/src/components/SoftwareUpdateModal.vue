<script setup lang="ts">

import Modal from "@/components/Modal.vue";
import UpdateIcon from "@/components/icons/UpdateIcon.vue";
import Button from "@/components/Button.vue";
import {useTemplateRef} from "vue";

const modal = useTemplateRef<typeof Modal>("modal");

const show = () => {
  modal.value?.openDialog();
};

defineExpose({show});

</script>

<template>
  <Modal title="Software Update" id="update-modal" ref="modal">
    <div id="update-content">
      <UpdateIcon id="update-icon"/>
      <div class="nav">
        <Button>Firmware</Button>
        <Button>Filesystem</Button>
      </div>
    </div>
  </Modal>
</template>

<style scoped>
  #update-modal {
    width: 40rem;
  }

  #update-content {
    padding: 10rem;
    display: flex;
    align-items: center;
    flex-direction: column;
  }

  #update-icon {
    color: cornflowerblue;
    width: 10rem;
  }
</style>