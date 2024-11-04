import { fileURLToPath, URL } from 'node:url'

import {build, defineConfig} from 'vite'
import vue from '@vitejs/plugin-vue'
import compression from "vite-plugin-compression2";

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    vue(),
    /*compression(
        {
          deleteOriginalAssets: true
        })*/
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
  build: {
    rollupOptions: {
      output: {
        assetFileNames: 'assets/[name][extname]',
        chunkFileNames: 'assets/[name].js',
        entryFileNames: 'assets/[name].js',
      }
    }
  }
})
